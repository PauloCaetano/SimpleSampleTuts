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

#ifndef LI_OUTOP_H
#define LI_OUTOP_H

#include "macro_overload_base.h"

// Because we have a unary operator, this interface is very simple.
// We just need one level of indirection for the ## concatenation.
#define PCBASE__LOG_ABSTRACTION(level, ...) PCBASE__LOGIMPL(level, __VA_ARGS__)

// Finally, we've got the call to the actual logging macros.
// These must be #defined in the user-supplied header, with the invocation to the
// logging implementation.
// This is the example of what is #defined in both poco_log.h and boost_log.h, for the
// stream interface.
//#define PCBASE__LOGIMPL(level, ...)
//    PCBLUESY__##level(PCBASE__MOVERLOAD_FOR_EACH(<<, "[", __FILE__, ":", __LINE__, "] ", __VA_ARGS__))

#endif // LI_OUTOP_H
