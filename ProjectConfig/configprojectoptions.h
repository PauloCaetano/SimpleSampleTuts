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

#ifndef CONFIGPROJECTOPTIONS_H
#define CONFIGPROJECTOPTIONS_H

#include "app_config/prog_options.h"

#include <iostream>
#include <string>

class ConfigProjectOptions
{
public:
    void DefineOptions(po::options_description& desc);
    std::string GetHelpOption() const { return "help"; }
    void Validate();

    std::string GetProjectName() const { return project_name; }
    std::string GetProjectType() const { return project_type; }
    bool WantGit() const { return init_git; }

    bool IsQtcProject() const { return is_qtc_project; }
    bool IsMsvcProject() const { return is_msvc_project; }

private:
    friend std::ostream& operator<<(std::ostream& os, ConfigProjectOptions const& obj);

    std::string project_name;
    std::string project_type;
    bool init_git = false;
    bool is_qtc_project = false;
    bool is_msvc_project = false;
};

#endif // CONFIGPROJECTOPTIONS_H
