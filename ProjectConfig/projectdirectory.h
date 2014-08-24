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

#ifndef PROJECTDIRECTORY_H
#define PROJECTDIRECTORY_H

#include <string>
#include <vector>

void ConfigureGit(std::string path_to_config);


class ProjectDirectory
{
public:
    ProjectDirectory(std::string home_path, std::string proj_name,
        std::vector<std::string> const& dir_structure, bool should_exist) :
        home{home_path}, projectName{proj_name}, structure{dir_structure}
    { ValidateProjectDirExistence(should_exist); }

    std::string GetHome() const { return home; }
    std::string GetProjectHomeDir() const { return GetHome() + projectName + "/"; }
    std::string GetGccDir() const { return GetProjectHomeDir() + structure[1]; }
    std::string GetMsvcDir() const { return GetProjectHomeDir() + structure[0]; }
    std::string GetQtcDir() const { return GetProjectHomeDir() + structure[1]; }

    void ValidateProjectDirExistence(bool should_exist) const;
    void CreateStructure() const;
private:
    std::string home;
    std::string projectName;
    std::vector<std::string> structure;
};



template <typename StgValidator, typename ProjectCopier, typename ConfigUpdater>
class Project
{
public:
    Project(std::string p_name, ProjectDirectory const& prj_dir,
        ProjectDirectory const& bld_dir, ProjectDirectory const& stg_dir) :
        name{p_name}, prjDirectory(prj_dir), bldDirectory(bld_dir), stgDirectory(stg_dir)
    { ValidateStgDir(); }

    void ValidateStgDir() const { StgValidator::Validate(stgDirectory); }
    void Copy() const
    {
        ProjectCopier::Copy(stgDirectory, prjDirectory);
        ConfigUpdater::Update(prjDirectory, bldDirectory);
    }
private:
    std::string name;
    ProjectDirectory const& prjDirectory;
    ProjectDirectory const& bldDirectory;
    ProjectDirectory const& stgDirectory;
};


struct QtcStgValidator
{
    static void Validate(ProjectDirectory const&);
};

struct MsvcStgValidator
{
    static void Validate(ProjectDirectory const&);
};

struct QtcCopier
{
    static void Copy(ProjectDirectory const& from, ProjectDirectory const& to);
};

struct MsvcCopier
{
    static void Copy(ProjectDirectory const& from, ProjectDirectory const& to);
};


struct QtcProjectConfigUpdater
{
    static void Update(ProjectDirectory const&, ProjectDirectory const&);
};


struct MsvcProjectConfigUpdater
{
    static void Update(ProjectDirectory const&, ProjectDirectory const&);
};

#endif // PROJECTDIRECTORY_H
