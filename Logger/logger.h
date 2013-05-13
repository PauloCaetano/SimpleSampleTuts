#ifndef LOGGER_H
#define LOGGER_H

#include "Poco/Logger.h"

#include <string>

namespace Lib {

class Logger
{
public:
    Logger() /* = delete */;
    explicit Logger(std::string const& loggerName);
    ~Logger() /* = default */;

    static void CreateLogger(std::string const& loggerName, std::string const& configFile);

    void Critical(std::string const& msg);
    void Debug(std::string const& msg1);
    void Error(std::string const& msg);
    void Fatal(std::string const& msg);
    void Information(std::string const& msg);
    void Notice(std::string const& msg);
    void Trace(std::string const& msg);
    void Warning(std::string const& msg);

private:
    Poco::Logger& m_logger;
};

inline
Logger::Logger(std::string const& loggerName) : m_logger(Poco::Logger::get(loggerName))
{
}

inline
void Logger::Critical(std::string const& msg)
{
    poco_critical(m_logger, msg);
}

inline
void Logger::Debug(std::string const& msg1)
{
    poco_debug(m_logger, msg1);
}

inline
void Logger::Error(std::string const& msg)
{
    poco_error(m_logger, msg);
}

inline
void Logger::Fatal(std::string const& msg)
{
    poco_fatal(m_logger, msg);
}

inline
void Logger::Information(std::string const& msg)
{
    poco_information(m_logger, msg);
}

inline
void Logger::Notice(std::string const& msg)
{
    poco_notice(m_logger, msg);
}

inline
void Logger::Trace(std::string const& msg)
{
    poco_trace(m_logger, msg);
}

inline
void Logger::Warning(std::string const& msg)
{
    poco_warning(m_logger, msg);
}

}
#endif // LOGGER_H
