// Copyright (c) 2014, Paulo Caetano
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of the copyright holder nor the names of any other
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "exception.h"
#include "projectdirectory.h"

#include "ms_windows/win_console_out.h"
using pt::pcaetano::bluesy::ms_windows::ConvertOutput;

#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;
using bfs::create_directory;
using bfs::current_path;
using bfs::directory_entry;
using bfs::directory_iterator;
using bfs::is_directory;
using bfs::path;
using bfs::rename;
#include <boost/regex.hpp>
using boost::regex;
using boost::regex_match;

#include <algorithm>
using std::count_if;
using std::for_each;
#include <cstdlib>
using std::system;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;


// C:\WinApp\Git\bin\sh.exe --login -i -c "git init"
void ConfigureGit(std::string path_to_config)
{
    path curr_path = current_path();
    path ptc{path_to_config};
    current_path(ptc);

    // TODO: Get path from config
//    int res = system("C:/WinApp/Git/bin/sh.exe --login -i -c \"git init\"");
    int res = system("I:/Apps/Git/bin/sh.exe --login -i -c \"git init\"");
    current_path(curr_path);

    if (res != 0)
    {
        BOOST_THROW_EXCEPTION(GitInitException{}
            << cp_error_string{"Erro ao inicializar git: " } << cp_error_id{res});
    }
}


bool DoesDirExist(string const& dir_path)
{
    return is_directory(dir_path);
}


unsigned int GetTotalSubdirs(string const& dir_path)
{
    path p{dir_path};
    // We need the lambda because the compiler doesn't
    // accept is_directory(), because directory_iterator
    // returns a directory_entry and is_directory() takes a path.
    return count_if(directory_iterator(p), directory_iterator(),
        [](directory_entry const& e) { return is_directory(e); });
}


// tool_root_dir is the root dir for the tool's project/solution file.
path GetProjectName(path const& tool_root_dir)
{
    return tool_root_dir.parent_path().filename();
}


// ASSUMES: We have a solution subdir if the directory we're given has
// a subdir with the same name as the previous dir.
bool HasSolutionSubdir(string const& dir_path)
{
    path p{dir_path};
    p /= GetProjectName(p);

    // Don't change the order here. If p is not a dir, we don't
    // want to check if it has subdirs.
    return (is_directory(p) && GetTotalSubdirs(p.string()) == 0);
}


// The name on these two functions is actually misleading, because these will copy
// anything, including dirs, not just files. But I haven't been able to come up
// with a better name yet, and I don't think separating it into different functions,
// for files and dirs, is worth the effort.
void CopyFiles(path const& from, path const& to)
{
    for_each(directory_iterator{from}, directory_iterator{},
        [&to](directory_entry const& e) { bfs::copy(e.path(), to / e.path().filename()); });
}


void CopyProjectFiles(string dir_from, string dir_to)
{
    path from{dir_from};
    path to{dir_to};

    CopyFiles(from, to);

    if (!HasSolutionSubdir(dir_from))
    {
        return;
    }

    from /= GetProjectName(from);
    to /= GetProjectName(to);

    CopyFiles(from, to);
}


void ProjectDirectory::ValidateProjectDirExistence(bool should_exist) const
{
    if (DoesDirExist(GetProjectHomeDir()) != should_exist)
    {
        BOOST_THROW_EXCEPTION(ProjectNameDirExists{}
            << cp_error_string{"Erro ao validar directoria " + GetProjectHomeDir()
            + ConvertOutput(". Directoria não deveria existir.")});
    }
}


void ProjectDirectory::CreateStructure() const
{
    path p{GetProjectHomeDir()};
    create_directory(p);

    for_each(structure.cbegin(), structure.cend(), [&p](string s) { create_directory(p / s);});
}


void QtcStgValidator::Validate(ProjectDirectory const& dir)
{
    if (GetTotalSubdirs(dir.GetQtcDir()) > 0)
    {
        BOOST_THROW_EXCEPTION(SubDirException{}
            << cp_error_string{"Erro ao validar a directoria STG de projecto Qt Creator: "
            + dir.GetQtcDir() + ". A directoria tem sub-directorias."});
    }
}


void MsvcStgValidator::Validate(ProjectDirectory const& dir)
{
    unsigned int tot_subdirs = GetTotalSubdirs(dir.GetMsvcDir());

    if (tot_subdirs == 0)
    {
        return;
    }

    if ((tot_subdirs == 1) && (HasSolutionSubdir(dir.GetMsvcDir())))
    {
        return;
    }

    BOOST_THROW_EXCEPTION(SubDirException{}
        << cp_error_string{"Erro ao validar a directoria STG de projecto MSVC: "
        + dir.GetMsvcDir() + ConvertOutput(". A directoria tem sub-directorias inválidas.")});
}


void QtcCopier::Copy(ProjectDirectory const& from, ProjectDirectory const& to)
{
    CopyProjectFiles(from.GetQtcDir(), to.GetQtcDir());
}


void MsvcCopier::Copy(ProjectDirectory const& from, ProjectDirectory const& to)
{
    CopyProjectFiles(from.GetMsvcDir(), to.GetMsvcDir());
}


void QtcProjectConfigUpdater::Update(ProjectDirectory const& proj_dir, ProjectDirectory const&)
{
    path orig_file{proj_dir.GetQtcDir()};
    string proj_name = GetProjectName(orig_file).generic_string();
    orig_file /= (proj_name + ".pro.user");
    path new_file{proj_dir.GetQtcDir()};
    new_file /= (proj_name + ".pro.user.new");

    ifstream inf{orig_file.generic_string()};
    ofstream outf{new_file.generic_string(), std::ios::out | std::ios::trunc};
    string line;

    while (getline(inf, line, inf.widen('\n')))
    {
        auto pos = line.find("Qt4ProjectManager.Qt4RunConfiguration:");
        if (pos != string::npos)
        {
            // We're taking some liberties here, because we know the exact value of a
            // key position on the line. 110 is the first character after the ":" on the
            // find() above.
            // In the end, we want to replace #1 with #2:
            // 1. F:/dev/Projects/stg/teste/qtc/teste.pro
            // 2. F:/dev/Projects/prj/teste/qtc/teste.pro
            auto endpos = line.find("<", 110);
            path p{proj_dir.GetQtcDir()};
            p /= (proj_name + ".pro");
            line.replace(110, endpos - 110, p.generic_string());
        }

        outf << line << '\n';
    }

    inf.close();
    outf.flush();
    outf.close();

    rename(new_file, orig_file);
}


void MsvcProjectConfigUpdater::Update(ProjectDirectory const& proj_dir,
    ProjectDirectory const& bld_dir)
{
    path orig_file{proj_dir.GetMsvcDir()};
    path new_file{proj_dir.GetMsvcDir()};
    string proj_name = GetProjectName(orig_file).generic_string();

    if (HasSolutionSubdir(proj_dir.GetMsvcDir()))
    {
        orig_file /= proj_name;
        new_file /= proj_name;
    }

    orig_file /= (proj_name + ".vcxproj");
    new_file /= (proj_name + ".vcxproj.new");

    ifstream inf{orig_file.generic_string()};
    ofstream outf{new_file.generic_string(), std::ios::out | std::ios::trunc};
    string line;
    regex const re("[[:blank:]]*<PropertyGroup.*[Debug|Release].*'\">");

    while (getline(inf, line, inf.widen('\n')))
    {
        outf << line << '\n';

        if (regex_match(line, re))
        {
            outf << "    <OutDir>" << bld_dir.GetMsvcDir() << "/$(Configuration)/out</OutDir>\n";
            outf << "    <IntDir>" << bld_dir.GetMsvcDir() << "/$(Configuration)/int</IntDir>\n";
        }
    }

    inf.close();
    outf.flush();
    outf.close();

    rename(new_file, orig_file);
}
