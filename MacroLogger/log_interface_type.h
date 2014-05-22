// Copyright (c) 2013-2014, Paulo Caetano
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

#ifndef LOG_INTERFACE_TYPE_H
#define LOG_INTERFACE_TYPE_H

// Logging interface types (LITs)
// Classifies the interface of the logging implementation used, regarding the way it
// accepts its arguments.

// The comma LIT accepts the arguments separated by commas.
// E.g., a printf-like interface, with a format string.
// TODO: Implement this interface type.
#define PCBLUESY__LOGINTERFACETYPE_COMMA 1

// The concatenation LIT accepts a single argument, which may result from
// the concatenation of several arguments.
// NOTE: This is not actually fully implemented. See li_concat.h.
#define PCBLUESY__LOGINTERFACETYPE_CONCAT 2

// The operator<< LIT uses stream syntax.
#define PCBLUESY__LOGINTERFACETYPE_OUTOP 3

#ifndef PCBLUESY__LOGINTERFACETYPE
#define PCBLUESY__LOGINTERFACETYPE PCBLUESY__LOGINTERFACETYPE_CONCAT
#endif

#if PCBLUESY__LOGINTERFACETYPE == PCBLUESY__LOGINTERFACETYPE_COMMA
#include "li_comma.h"
#endif

#if PCBLUESY__LOGINTERFACETYPE == PCBLUESY__LOGINTERFACETYPE_CONCAT
#include "li_concat.h"
#endif

#if PCBLUESY__LOGINTERFACETYPE == PCBLUESY__LOGINTERFACETYPE_OUTOP
#include "li_outop.h"
#endif

#endif // LOG_INTERFACE_TYPE_H
