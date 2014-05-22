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

#ifndef POCO_LOG_H
#define POCO_LOG_H

#include "macro_overload_base.h"

#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"
#include "Poco/LogStream.h"
using Poco::Logger;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Message;
using Poco::LogStream;

#if PCBLUESY__LOGINTERFACETYPE == PCBLUESY__LOGINTERFACETYPE_CONCAT
#define PCBLUESY__GETLOGGER(PCBLUESY_LOG_NAME) \
    Poco::Logger& PCBLUESY__POCOLOG = Poco::Logger::get(PCBLUESY_LOG_NAME)

#define PCBLUESY__LOG(level, ...) PCBASE__LOG_ABSTRACTION(level, __VA_ARGS__)

// Here's how it works with Poco Logger
#define PCBLUESY__PCBLUESY__TRACE(...) \
    poco_trace(PCBLUESY__POCOLOG, __VA_ARGS__)
#define PCBLUESY__PCBLUESY__DEBUG(...) \
    poco_debug(PCBLUESY__POCOLOG, __VA_ARGS__)
#define PCBLUESY__PCBLUESY__INFO(...) \
    poco_information(PCBLUESY__POCOLOG, __VA_ARGS__)
#define PCBLUESY__PCBLUESY__NOTICE(...) \
    poco_notice(PCBLUESY__POCOLOG, __VA_ARGS__)
#define PCBLUESY__PCBLUESY__WARNING(...) \
    poco_warning(PCBLUESY__POCOLOG, __VA_ARGS__)
#define PCBLUESY__PCBLUESY__ERROR(...) \
    poco_error(PCBLUESY__POCOLOG, __VA_ARGS__)
#define PCBLUESY__PCBLUESY__CRITICAL(...) \
    poco_critical(PCBLUESY__POCOLOG, __VA_ARGS__)
#define PCBLUESY__PCBLUESY__FATAL(...) \
    poco_fatal(PCBLUESY__POCOLOG, __VA_ARGS__)

#define PCBASE__LAMOVERLOAD_LOG_IMPL_1(level, ...) \
    PCBLUESY__##level(__VA_ARGS__)
#define PCBASE__LAMOVERLOAD_LOG_IMPL_2(level, x, ...) \
    PCBLUESY__##level((x) PCBASE__MOVERLOAD_FOR_EACH(+, __VA_ARGS__))
#endif

// Poco Logger's stream interface doesn't add __FILE__ and __LINE__ "automatically".
// That means we have to do it. I have yet to figure out how to do it in a "standard"
// Poco fashion, so I'll just prepend this to the message.
// This means we better remove these fields from the output line format spec.
#if PCBLUESY__LOGINTERFACETYPE == PCBLUESY__LOGINTERFACETYPE_OUTOP
#define PCBLUESY__GETLOGGER(PCBLUESY_LOG_NAME) \
    Poco::LogStream PCBLUESY__POCOLOG{Poco::Logger::get(PCBLUESY_LOG_NAME)}

#define PCBLUESY__LOG(level, ...) PCBASE__LOG_ABSTRACTION(level, __VA_ARGS__)

#define PCBLUESY__PCBLUESY__TRACE(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().trace()) PCBLUESY__POCOLOG.trace() __VA_ARGS__ << endl; else (void) 0
#define PCBLUESY__PCBLUESY__DEBUG(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().debug()) PCBLUESY__POCOLOG.debug() __VA_ARGS__ << endl; else (void) 0
#define PCBLUESY__PCBLUESY__INFO(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().information()) \
        PCBLUESY__POCOLOG.information() __VA_ARGS__ << endl; else (void) 0
#define PCBLUESY__PCBLUESY__NOTICE(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().notice()) PCBLUESY__POCOLOG.notice() __VA_ARGS__ << endl; else (void) 0
#define PCBLUESY__PCBLUESY__WARNING(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().warning()) \
        PCBLUESY__POCOLOG.warning() __VA_ARGS__ << endl; else (void) 0
#define PCBLUESY__PCBLUESY__ERROR(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().error()) PCBLUESY__POCOLOG.error() __VA_ARGS__ << endl; else (void) 0
#define PCBLUESY__PCBLUESY__CRITICAL(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().critical()) \
        PCBLUESY__POCOLOG.critical() __VA_ARGS__ << endl; else (void) 0
#define PCBLUESY__PCBLUESY__FATAL(...) \
    if (PCBLUESY__POCOLOG.rdbuf()->logger().fatal()) PCBLUESY__POCOLOG.fatal() __VA_ARGS__ << endl; else (void) 0

#define PCBASE__LOGIMPL(level, ...) \
    PCBLUESY__##level(PCBASE__MOVERLOAD_FOR_EACH(<<, "[", __FILE__, ":", __LINE__, "] ", __VA_ARGS__))
#endif

#endif // POCO_LOG_H
