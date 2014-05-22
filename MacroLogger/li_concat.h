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

#ifndef LI_CONCAT_H
#define LI_CONCAT_H

#include "macro_overload_base.h"

// !!!!!!!!
// NOTE: This is not actually working, because we're not converting automatically
// to string. This means the user must include this conversion in his code, whenever
// he invokes the logging mechanism.
// !!!!!!!!

// TODO: Solve the conversion-to-string problem, i.e., converting to string
//  whithout requiring it in the logging invocation code.
//  This is an example of what we want in the logging invocation code:
//  LOG_FUNCTION_MACRO(ERROR_DEFINE_MACRO,
//      "Blimey! I didn't expect the Spanish Inquisition!",
//      chiefWeapons, mill.Trouble(), 42);
//  It must be up to the macros defined in this header file to automatically invoke
//  the necessary conversions to string in order to perform the concatenation.


// Depending on whether we have one or more arguments, we want to perform
// different actions, because we can't concatenate a single argument.
#define PCBASE__LOG_ABSTRACTION(level, ...) \
    PCBASE__LAMOVERLOAD_IND(PCBASE__MOVERLOAD_ONE_ARG_OR_MORE(__VA_ARGS__))(level, __VA_ARGS__)

// We need to go through MYTESTLOG_OVERLOAD_IND to ensure correct token
// substitution on the ## concatenation.
#define PCBASE__LAMOVERLOAD_IND(N, ...) PCBASE__LAMOVERLOAD_IMPL(N, __VA_ARGS__)

// Here, we perform the "overloading", calling the correct macro for the number
// of arguments, which can either be one or more than one.
#define PCBASE__LAMOVERLOAD_IMPL(N, ...) PCBASE__LAMOVERLOAD_LOG_IND_##N

// These two macros have the same role as MYTESTLOG_OVERLOAD_IND, above.
// We're "overloading" the macros based on the number of arguments, and
// we care for two cases - one argument, and more than one argument.
#define PCBASE__LAMOVERLOAD_LOG_IND_1(level, x) PCBASE__LAMOVERLOAD_LOG_IMPL_1(level, x)
#define PCBASE__LAMOVERLOAD_LOG_IND_2(level, x, ...) PCBASE__LAMOVERLOAD_LOG_IMPL_2(level, x, __VA_ARGS__)

// Finally, we've got the call to the actual logging macros.
// These must be #defined in the user-supplied header, with the invocation to the
// logging implementation.
// This is the example of what is #defined in poco_log.h, for the concatenation
// interface.
//#define PCBASE__LAMOVERLOAD_LOG_IMPL_1(level, ...) PCBLUESY__##level(__VA_ARGS__)
//#define PCBASE__LAMOVERLOAD_LOG_IMPL_2(level, x, ...) PCBLUESY__##level((x) PCBASE__MOVERLOAD_FOR_EACH(+, __VA_ARGS__))


#endif // LI_CONCAT_H
