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
#include "app_config/appconfigexception.h"
using pt::pcaetano::bluesy::config::config_error_string;
using pt::pcaetano::bluesy::config::ConfigInvalidOption;

#include <boost/program_options.hpp>
using boost::program_options::options_description;
using boost::program_options::validators::check_first_occurrence;
using boost::program_options::validators::get_single_string;
using boost::program_options::validation_error;
using boost::program_options::value;
using boost::program_options::bool_switch;

#include <algorithm>
using std::find;
#include <iostream>
using std::ostream;
#include <iterator>
using std::begin;
using std::end;
#include <string>
using std::string;
#include <vector>
using std::vector;

char const* valid_project_types[] = { "qtc", "msvc", "both" };

void ConfigProjectOptions::DefineOptions(options_description& desc)
{
    desc.add_options()
        ("help,h", "Mensagem de ajuda")
        ("project,p", value<string>(&project_name)->required(), "Nome do projecto. Obrigatório.")
        ("type,t", value<string>(&project_type)->default_value("both"), "Tipo do projecto."
             " Pode ser \"qtc\" (Qt Creator), \"msvc\" (VC++)"
             " e \"both\" (ambos). Opcional, default: \"both\"")
        ("initgit,g", bool_switch(&init_git)->default_value(false), "Se pretender criar um repositório git para"
             " os projectos, inclua esta opção. O repositório é criado ao nível da home dir do projecto, "
             " incluindo automaticamente ambos os tipos de projecto e as sources. Opcional, default: false")
    ;
}

void ConfigProjectOptions::Validate()
{
    auto const e = end(valid_project_types);
    auto const res = find(begin(valid_project_types), e, project_type);

    if (res == e)
    {
        BOOST_THROW_EXCEPTION(ConfigInvalidOption()
            << config_error_string("Tipo de projecto inválido: " + project_type));
    }

    // Although these are not, strictly speaking, validations,
    // we can calculate them here, only once.
    // A bit hackish, as we're taking advantage of the fact that the first character
    // of each option is different.
    if (*res[0] == 'b')
    {
        is_qtc_project = is_msvc_project = true;
        return;
    }

    if (*res[0] == 'q')
    {
        is_qtc_project = true;
        return;
    }

    if (*res[0] == 'm')
    {
        is_msvc_project = true;
    }
}


ostream& operator<<(ostream& os, ConfigProjectOptions const& obj)
{
    os << "Projecto: " << obj.project_name << " (" << obj.project_type << "), "
        << (obj.init_git ? "com git" : "sem git");

    return os;
}
