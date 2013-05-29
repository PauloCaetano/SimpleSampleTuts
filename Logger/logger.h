#ifndef LOGGER_H
#define LOGGER_H

#include "Poco/Logger.h"

#include <string>

namespace Lib {

class Logger
{
public:
    Logger() /* = delete */;
    explicit Logger(std::string const& loggerName, char const* file = nullptr);
    ~Logger() /* = default */;

    static void CreateLogger(std::string const& loggerName, std::string const& configFile);

    bool IsCritical() const;
    bool IsDebug() const;
    bool IsError() const;
    bool IsFatal() const;
    bool IsInformation() const;
    bool IsNotice() const;
    bool IsTrace() const;
    bool IsWarning() const;

    void Critical(std::string const& msg);
    void Debug(std::string const& msg);
    void Error(std::string const& msg);
    void Fatal(std::string const& msg);
    void Information(std::string const& msg);
    void Notice(std::string const& msg);
    void Trace(std::string const& msg);
    void Warning(std::string const& msg);

    void Critical(std::string const& msg, int line);
    void Debug(std::string const& msg, int line);
    void Error(std::string const& msg, int line);
    void Fatal(std::string const& msg, int line);
    void Information(std::string const& msg, int line);
    void Notice(std::string const& msg, int line);
    void Trace(std::string const& msg, int line);
    void Warning(std::string const& msg, int line);

private:
    Poco::Logger& m_logger;
    char const* m_file;
};

inline
Logger::Logger(std::string const& loggerName, char const* file) :
    m_logger(Poco::Logger::get(loggerName)), m_file(file)
{
}

inline
bool Logger::IsCritical() const
{
    return m_logger.critical();
}

inline
bool Logger::IsDebug() const
{
    return m_logger.debug();
}

inline
bool Logger::IsError() const
{
    return m_logger.error();
}

inline
bool Logger::IsFatal() const
{
    return m_logger.fatal();
}

inline
bool Logger::IsInformation() const
{
    return m_logger.information();
}

inline
bool Logger::IsNotice() const
{
    return m_logger.notice();
}

inline
bool Logger::IsTrace() const
{
    return m_logger.trace();
}

inline
bool Logger::IsWarning() const
{
    return m_logger.warning();
}

inline
void Logger::Critical(std::string const& msg)
{
    m_logger.critical(msg);
}

inline
void Logger::Debug(std::string const& msg)
{
    m_logger.debug(msg);
}

inline
void Logger::Error(std::string const& msg)
{
    m_logger.error(msg);
}

inline
void Logger::Fatal(std::string const& msg)
{
    m_logger.fatal(msg);
}

inline
void Logger::Information(std::string const& msg)
{
    m_logger.information(msg);
}

inline
void Logger::Notice(std::string const& msg)
{
    m_logger.notice(msg);
}

inline
void Logger::Trace(std::string const& msg)
{
    m_logger.trace(msg);
}

inline
void Logger::Warning(std::string const& msg)
{
    m_logger.warning(msg);
}


inline
void Logger::Critical(std::string const& msg, int line)
{
    m_logger.critical(msg, m_file, line);
}

inline
void Logger::Debug(std::string const& msg, int line)
{
    m_logger.debug(msg, m_file, line);
}

inline
void Logger::Error(std::string const& msg, int line)
{
    m_logger.error(msg, m_file, line);
}

inline
void Logger::Fatal(std::string const& msg, int line)
{
    m_logger.fatal(msg, m_file, line);
}

inline
void Logger::Information(std::string const& msg, int line)
{
    m_logger.information(msg, m_file, line);
}

inline
void Logger::Notice(std::string const& msg, int line)
{
    m_logger.notice(msg, m_file, line);
}

inline
void Logger::Trace(std::string const& msg, int line)
{
    m_logger.trace(msg, m_file, line);
}

inline
void Logger::Warning(std::string const& msg, int line)
{
    m_logger.warning(msg, m_file, line);
}


}
#endif // LOGGER_H
