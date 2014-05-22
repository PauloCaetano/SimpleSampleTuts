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

#ifndef BOOST_LOG_H
#define BOOST_LOG_H

//#include "macro_overload_base.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#define BOOST_LOG_DYN_LINK
#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>

#include <boost/log/support/date_time.hpp>
#pragma GCC diagnostic pop

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

#define PCBLUESY__GETLOGGER(PCBLUESY_LOG_NAME) \
    src::severity_logger<boost::log::trivial::severity_level> PCBLUESY__BOOSTLOG

#define PCBLUESY__LOG(level, ...) PCBASE__LOG_ABSTRACTION(level, __VA_ARGS__)

#define PCBLUESY__PCBLUESY__TRACE(...) \
    BOOST_LOG_SEV(PCBLUESY__BOOSTLOG, boost::log::trivial::severity_level::trace) __VA_ARGS__
#define PCBLUESY__PCBLUESY__DEBUG(...) \
    BOOST_LOG_SEV(PCBLUESY__BOOSTLOG, boost::log::trivial::severity_level::debug) __VA_ARGS__
#define PCBLUESY__PCBLUESY__INFO(...) \
    BOOST_LOG_SEV(PCBLUESY__BOOSTLOG, boost::log::trivial::severity_level::info) __VA_ARGS__
#define PCBLUESY__PCBLUESY__WARNING(...) \
    BOOST_LOG_SEV(PCBLUESY__BOOSTLOG, boost::log::trivial::severity_level::warning) __VA_ARGS__
#define PCBLUESY__PCBLUESY__ERROR(...) \
    BOOST_LOG_SEV(PCBLUESY__BOOSTLOG, boost::log::trivial::severity_level::error) __VA_ARGS__
#define PCBLUESY__PCBLUESY__FATAL(...) \
    BOOST_LOG_SEV(PCBLUESY__BOOSTLOG, boost::log::trivial::severity_level::fatal) __VA_ARGS__

#define PCBASE__LOGIMPL(level, ...) \
    PCBLUESY__##level(PCBASE__MOVERLOAD_FOR_EACH(<<, "[", __FILE__, ":", __LINE__, "] ", __VA_ARGS__))

#endif // BOOST_LOG_H
