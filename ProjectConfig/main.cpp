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

#include "configprojectoptions.h"
#include "projectdirectory.h"

#include "app_config/prog_options.h"
using pt::pcaetano::bluesy::config::AppOptions;
#include "ms_windows/win_console_out.h"
using pt::pcaetano::bluesy::ms_windows::ConvertOutput;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string.hpp>
using boost::to_upper;
#pragma GCC diagnostic pop
#include <boost/exception/all.hpp>
using boost::diagnostic_information;

#include <iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
#include <iterator>
using std::begin;
using std::end;
#include <string>
using std::getline;
using std::string;
#include <vector>
using std::vector;

// Paths to relevant directories
// TODO: These must come from configuration files
//  - See Boost ProprtyTree
string const PROJ_HOME = "F:/dev/Projects/";
string const PROJ_STG = "F:/dev/Projects/stg/";
string const PROJ_PRJ = "F:/dev/Projects/prj/";
string const PROJ_BLD = "F:/dev/Projects/bld/";
//string const PROJ_HOME = "C:/MyApps/Projects/";
//string const PROJ_STG = "C:/MyApps/Projects/stg/";
//string const PROJ_PRJ = "C:/MyApps/Projects/prj/";
//string const PROJ_BLD = "C:/MyApps/Projects/bld/";

// The order os these directories must always be:
// - msvc, qtc/gcc, etc.
// This order is essential for the correct functioning of the
// ProjectDirectory class
vector<string> const STRUCT_PRJ{ "msvc", "qtc", "src", "doc" };
vector<string> const STRUCT_BLD{ "vc", "gcc" };
vector<string> const STRUCT_STG{ "msvc", "qtc" };

bool constexpr SHOULD_EXIST = true;
bool constexpr SHOULD_NOT_EXIST = !SHOULD_EXIST;

bool UserConfirms(string proj_name)
{
    cout << ConvertOutput("Todas as validações foram efectuadas, pronto para copiar os ficheiros e "
        "alterar as configurações (caso algo não corra como esperado, basta eliminar a directoria '");
    cout << proj_name;
    cout << ConvertOutput("' nas directorias 'prj' e 'bld')\n");

    string answer = "";
    while (true)
    {
        cout << ConvertOutput("Confirma a operação (s/N)? ");
        getline(cin, answer);
        to_upper(answer);

        if (answer == "S")
        {
            cout << ConvertOutput("Operação confirmada.\n");
            return true;
        }

        if ((answer == "N") || (answer == ""))
        {
            cout << ConvertOutput("Operação NÃO confirmada.\n");
            return false;
        }

        cout << ConvertOutput("A resposta tem que ser 'S' ou 'N'. O default é 'N'.\n");
    }
}


void Run(int argc, char *argv[])
{
    AppOptions<ConfigProjectOptions> ao{argc, argv, "Opções ProjectConfig"};

    if (ao.HaveShownHelp())
    {
        return;
    }

    ConfigProjectOptions const& opt = ao.GetOptions();
    string project_name = opt.GetProjectName();

    // All objects are validated on construction.
    ProjectDirectory prj_dir(PROJ_PRJ, project_name, STRUCT_PRJ, SHOULD_NOT_EXIST);
    ProjectDirectory bld_dir(PROJ_BLD, project_name, STRUCT_BLD, SHOULD_NOT_EXIST);
    ProjectDirectory stg_dir(PROJ_STG, project_name, STRUCT_STG, SHOULD_EXIST);

    Project<QtcStgValidator, QtcCopier, QtcProjectConfigUpdater>
        qtc_project{project_name, prj_dir, bld_dir, stg_dir};
    Project<MsvcStgValidator, MsvcCopier, MsvcProjectConfigUpdater>
        msvc_project(project_name, prj_dir, bld_dir, stg_dir);

    // Everything is valid, get user confirmation.
    if (!UserConfirms(project_name))
    {
        return;
    }

    prj_dir.CreateStructure();
    bld_dir.CreateStructure();

    if (opt.WantGit())
    {
        ConfigureGit(prj_dir.GetProjectHomeDir());
    }

    if (opt.IsQtcProject())
    {
        qtc_project.Copy();
    }

    if (opt.IsMsvcProject())
    {
        msvc_project.Copy();
    }
}


int main(int argc, char *argv[])
{
    try
    {
        Run(argc, argv);
    }
    catch (std::exception& ex)
    {
        cerr << diagnostic_information(ex) << endl;
        exit(1);
    }
}
