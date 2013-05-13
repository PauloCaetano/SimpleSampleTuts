#ifndef LoggerBridge_H
#define LoggerBridge_H

#include <string>

namespace Lib {

template <bool condition, typename LoggerImpl>
class LoggerBridge
{
public:
    explicit LoggerBridge(std::string const& loggerName);

    static void CreateLogger(std::string const& loggerName, std::string const& configFile);

    void Critical(std::string const& msg);
    void Debug(std::string const& msg);
    void Error(std::string const& msg);
    void Fatal(std::string const& msg);
    void Information(std::string const& msg);
    void Notice(std::string const& msg);
    void Trace(std::string const& msg);
    void Warning(std::string const& msg);
private:
    LoggerImpl l;
};


template <typename LoggerImpl>
class LoggerBridge<false, LoggerImpl>
{
public:
    explicit LoggerBridge(std::string /*const& loggerName*/) {}

    static void CreateLogger(std::string /*const& loggerName*/, std::string const& /*configFile*/) {}

    void Critical(std::string const& /*msg*/) {}
    void Debug(std::string const& /*msg*/) {}
    void Error(std::string const& /*msg*/) {}
    void Fatal(std::string const& /*msg*/) {}
    void Information(std::string const& /*msg*/) {}
    void Notice(std::string const& /*msg*/) {}
    void Trace(std::string const& /*msg*/) {}
    void Warning(std::string const& /*msg*/) {}
};

template <bool condition, typename LoggerImpl>
LoggerBridge<condition, LoggerImpl>::LoggerBridge(std::string const& loggerName) : l(loggerName)
{
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::CreateLogger(std::string const& loggerName, std::string const& configFile)
{
    LoggerImpl::CreateLogger(loggerName, configFile);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Critical(std::string const& msg)
{
    l.Critical(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Debug(std::string const& msg)
{
    l.Debug(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Error(std::string const& msg)
{
    l.Error(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Fatal(std::string const& msg)
{
    l.Fatal(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Information(std::string const& msg)
{
    l.Information(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Notice(std::string const& msg)
{
    l.Notice(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Trace(std::string const& msg)
{
    l.Trace(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Warning(std::string const& msg)
{
    l.Warning(msg);
}

}
#endif // LoggerBridge_H
