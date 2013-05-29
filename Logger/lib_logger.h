#ifndef LIB_LOGGER_H
#define LIB_LOGGER_H

//#include "logger.h"
#include "loggercout.h"
#include "loggerbridge.h"
//typedef Lib::Logger LoggerImplementation;
typedef SomethingElse::LoggerCout LoggerImplementation;
typedef Lib::LoggerBridge<WANT_LOGGING, LoggerImplementation> LibLogger;
//typedef Lib::LoggerBridge<false, LoggerImplementation> LibLogger;

// USE GETLOGGER WHEN YOU FETCH A SINGLE LOGGER FOR AN ENTIRE SCOPE (e.g., A FUNCTION).
// USE GET LOGGER_VAR WHAN YOU NEED MORE THAN 1 LOGGER ON AN ENTIRE SCOPE; INSTEAD OF USING THE
// DEFAULT PC_LIBLOGGER_PC IDENTIFIER, IT'LL USE THE ONE YOU SUPPLY IN "var".
#define PCLIB_GETLOGGER_VAR(var, name) LibLogger var((name), __FILE__)
#define PCLIB_GETLOGGER(name) PCLIB_GETLOGGER_VAR(PC_LIBLOGGER_PC, name)

// USE THE CHECK MACROS (e.g., PCLIB_LOGGER_CRITICAL_CHECK OR PCLIB_LOGGER_CRITICAL_CHECK_VAR)
// WHEN YOU'RE LOGGING ONE MESSAGE AT A TIME. USE THE NON-CHECK MACROS WHEN YOU'RE GOING TO
// CHECK THE LOGGING LEVEL ONCE AND THEN LOG SEVERAL MESSAGES; THIS WAY, YOU'LL AVOID CHECKING
// THE LOGGING LEVEL FOR EACH MESSAGE

// IN MSVC, WE NEED ANOTHER "ADAPTATION" - SINCE WE MUST SPECIFY THE TEMPLATE ARGUMENT ON INVOCATION,
// WE GET IN TROUBLE WHEN WE USE OUR LoggerBridge<false, etc> SPECIALIZATION, BECAUSE ITS MEMBER FUNCTIONS
// ARE NOT TEMPLATE FUNCTIONS. SO, WE HAVE DIFFERENT MACROS, DEPENDING ON THE VALUE OF WANT_LOGGING.
// WHEN MSVC ACCEPTS DEFAULT TEMPLATE ARGUMENTS TO TEMPLATE FUNCTIONS, WE WON'T NEED ANY OF THIS

#ifdef _MSC_VER
#if WANT_LOGGING
#define PCLIB_LOGGER_CRITICAL_VAR(var, msg) (var).Critical<LoggerImplementation>((msg), __LINE__)
#define PCLIB_LOGGER_DEBUG_VAR(var, msg) (var).Debug<LoggerImplementation>((msg), __LINE__)
#define PCLIB_LOGGER_ERROR_VAR(var, msg) (var).Error<LoggerImplementation>((msg), __LINE__)
#define PCLIB_LOGGER_FATAL_VAR(var, msg) (var).Fatal<LoggerImplementation>((msg), __LINE__)
#define PCLIB_LOGGER_INFORMATION_VAR(var, msg) (var).Information<LoggerImplementation>((msg), __LINE__)
#define PCLIB_LOGGER_NOTICE_VAR(var, msg) (var).Notice<LoggerImplementation>((msg), __LINE__)
#define PCLIB_LOGGER_TRACE_VAR(var, msg) (var).Trace<LoggerImplementation>((msg), __LINE__)
#define PCLIB_LOGGER_WARNING_VAR(var, msg) (var).Warning<LoggerImplementation>((msg), __LINE__)

// THE FOLLOWING IDEA/FUNCTIONALITY IS BASED UPON POCO'S Logger poco_* MACROS
#define PCLIB_LOGGER_CRITICAL_CHECK_VAR(var, msg) \
    if ((var).IsCritical()) (var).Critical<LoggerImplementation>((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_DEBUG_CHECK_VAR(var, msg) \
    if ((var).IsDebug()) (var).Debug<LoggerImplementation>((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_ERROR_CHECK_VAR(var, msg) \
    if ((var).IsError()) (var).Error<LoggerImplementation>((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_FATAL_CHECK_VAR(var, msg) \
    if ((var).IsFatal()) (var).Fatal<LoggerImplementation>((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_INFORMATION_CHECK_VAR(var, msg) \
    if ((var).IsInformation()) (var).Information<LoggerImplementation>((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_NOTICE_CHECK_VAR(var, msg) \
    if ((var).IsNotice()) (var).Notice<LoggerImplementation>((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_TRACE_CHECK_VAR(var, msg) \
    if ((var).IsTrace()) (var).Trace<LoggerImplementation>((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_WARNING_CHECK_VAR(var, msg) \
    if ((var).IsWarning()) (var).Warning<LoggerImplementation>((msg), __LINE__); else (void) 0

#else // WANT_LOGGING
#define PCLIB_LOGGER_CRITICAL_VAR(var, msg) (var).Critical((msg), __LINE__)
#define PCLIB_LOGGER_DEBUG_VAR(var, msg) (var).Debug((msg), __LINE__)
#define PCLIB_LOGGER_ERROR_VAR(var, msg) (var).Error((msg), __LINE__)
#define PCLIB_LOGGER_FATAL_VAR(var, msg) (var).Fatal((msg), __LINE__)
#define PCLIB_LOGGER_INFORMATION_VAR(var, msg) (var).Information((msg), __LINE__)
#define PCLIB_LOGGER_NOTICE_VAR(var, msg) (var).Notice((msg), __LINE__)
#define PCLIB_LOGGER_TRACE_VAR(var, msg) (var).Trace((msg), __LINE__)
#define PCLIB_LOGGER_WARNING_VAR(var, msg) (var).Warning((msg), __LINE__)

#define PCLIB_LOGGER_CRITICAL_CHECK_VAR(var, msg)
#define PCLIB_LOGGER_DEBUG_CHECK_VAR(var, msg)
#define PCLIB_LOGGER_ERROR_CHECK_VAR(var, msg)
#define PCLIB_LOGGER_FATAL_CHECK_VAR(var, msg)
#define PCLIB_LOGGER_INFORMATION_CHECK_VAR(var, msg)
#define PCLIB_LOGGER_NOTICE_CHECK_VAR(var, msg)
#define PCLIB_LOGGER_TRACE_CHECK_VAR(var, msg)
#define PCLIB_LOGGER_WARNING_CHECK_VAR(var, msg)
#endif // WANT_LOGGING

#else // _MSC_VER
#define PCLIB_LOGGER_CRITICAL_VAR(var, msg) (var).Critical((msg), __LINE__)
#define PCLIB_LOGGER_DEBUG_VAR(var, msg) (var).Debug((msg), __LINE__)
#define PCLIB_LOGGER_ERROR_VAR(var, msg) (var).Error((msg), __LINE__)
#define PCLIB_LOGGER_FATAL_VAR(var, msg) (var).Fatal((msg), __LINE__)
#define PCLIB_LOGGER_INFORMATION_VAR(var, msg) (var).Information((msg), __LINE__)
#define PCLIB_LOGGER_NOTICE_VAR(var, msg) (var).Notice((msg), __LINE__)
#define PCLIB_LOGGER_TRACE_VAR(var, msg) (var).Trace((msg), __LINE__)
#define PCLIB_LOGGER_WARNING_VAR(var, msg) (var).Warning((msg), __LINE__)

// THE FOLLOWING IDEA/FUNCTIONALITY IS BASED UPON POCO'S Logger poco_* MACROS
#define PCLIB_LOGGER_CRITICAL_CHECK_VAR(var, msg) \
    if ((var).IsCritical()) (var).Critical((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_DEBUG_CHECK_VAR(var, msg) \
    if ((var).IsDebug()) (var).Debug((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_ERROR_CHECK_VAR(var, msg) \
    if ((var).IsError()) (var).Error((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_FATAL_CHECK_VAR(var, msg) \
    if ((var).IsFatal()) (var).Fatal((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_INFORMATION_CHECK_VAR(var, msg) \
    if ((var).IsInformation()) (var).Information((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_NOTICE_CHECK_VAR(var, msg) \
    if ((var).IsNotice()) (var).Notice((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_TRACE_CHECK_VAR(var, msg) \
    if ((var).IsTrace()) (var).Trace((msg), __LINE__); else (void) 0
#define PCLIB_LOGGER_WARNING_CHECK_VAR(var, msg) \
    if ((var).IsWarning()) (var).Warning((msg), __LINE__); else (void) 0
#endif // _MSC_VER

#define PCLIB_LOGGER_CRITICAL(msg) PCLIB_LOGGER_CRITICAL_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_DEBUG(msg) PCLIB_LOGGER_DEBUG_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_ERROR(msg) PCLIB_LOGGER_ERROR_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_FATAL(msg) PCLIB_LOGGER_FATAL_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_INFORMATION(msg) PCLIB_LOGGER_INFORMATION_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_NOTICE(msg) PCLIB_LOGGER_NOTICE_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_TRACE(msg) PCLIB_LOGGER_TRACE_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_WARNING(msg) PCLIB_LOGGER_WARNING_VAR(PC_LIBLOGGER_PC, (msg))

#define PCLIB_LOGGER_CRITICAL_CHECK(msg) PCLIB_LOGGER_CRITICAL_CHECK_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_DEBUG_CHECK(msg) PCLIB_LOGGER_DEBUG_CHECK_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_ERROR_CHECK(msg) PCLIB_LOGGER_ERROR_CHECK_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_FATAL_CHECK(msg) PCLIB_LOGGER_FATAL_CHECK_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_INFORMATION_CHECK(msg) PCLIB_LOGGER_INFORMATION_CHECK_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_NOTICE_CHECK(msg) PCLIB_LOGGER_NOTICE_CHECK_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_TRACE_CHECK(msg) PCLIB_LOGGER_TRACE_CHECK_VAR(PC_LIBLOGGER_PC, (msg))
#define PCLIB_LOGGER_WARNING_CHECK(msg) PCLIB_LOGGER_WARNING_CHECK_VAR(PC_LIBLOGGER_PC, (msg))

#endif // LIB_LOGGER_H
