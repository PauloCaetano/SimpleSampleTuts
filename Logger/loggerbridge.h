#ifndef LoggerBridge_H
#define LoggerBridge_H

#include "checklibinterface.h"

#include <string>
#include <type_traits>

#ifdef _MSC_VER
#define TEMPLATE_TYPENAME_LI template <typename LI>
#else
#define TEMPLATE_TYPENAME_LI template <typename LI = LoggerImpl>
#endif

namespace Lib {

template <bool condition, typename LoggerImpl>
class LoggerBridge
{
public:
    explicit LoggerBridge(std::string const& loggerName, char const* file = nullptr);

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

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesCritical<LI, void, std::string const&, int>::Exist, void>::type
    Critical(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesCritical<LI, void, std::string const&, int>::Exist, void>::type
    Critical(std::string const&, int);

    void Debug(std::string const& msg);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesDebug<LI, void, std::string const&, int>::Exist, void>::type
    Debug(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesDebug<LI, void, std::string const&, int>::Exist, void>::type
    Debug(std::string const&, int);

    void Error(std::string const& msg);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesError<LI, void, std::string const&, int>::Exist, void>::type
    Error(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesError<LI, void, std::string const&, int>::Exist, void>::type
    Error(std::string const&, int);

    void Fatal(std::string const& msg);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesFatal<LI, void, std::string const&, int>::Exist, void>::type
    Fatal(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesFatal<LI, void, std::string const&, int>::Exist, void>::type
    Fatal(std::string const&, int);

    void Information(std::string const& msg);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesInformation<LI, void, std::string const&, int>::Exist, void>::type
    Information(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesInformation<LI, void, std::string const&, int>::Exist, void>::type
    Information(std::string const&, int);

    void Notice(std::string const& msg);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesNotice<LI, void, std::string const&, int>::Exist, void>::type
    Notice(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesNotice<LI, void, std::string const&, int>::Exist, void>::type
    Notice(std::string const&, int);

    void Trace(std::string const& msg);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesTrace<LI, void, std::string const&, int>::Exist, void>::type
    Trace(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesTrace<LI, void, std::string const&, int>::Exist, void>::type
    Trace(std::string const&, int);

    void Warning(std::string const& msg);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<DoesWarning<LI, void, std::string const&, int>::Exist, void>::type
    Warning(std::string const&, int);

    TEMPLATE_TYPENAME_LI
    typename std::enable_if<!DoesWarning<LI, void, std::string const&, int>::Exist, void>::type
    Warning(std::string const&, int);
private:
    LoggerImpl l;
};


template <typename LoggerImpl>
class LoggerBridge<false, LoggerImpl>
{
public:
    explicit LoggerBridge(std::string const&, const char*) {}

    static void CreateLogger(std::string const&, std::string const&) {}

#ifndef _MSC_VER
    constexpr
#endif
    bool IsCritical() const { return false; }

#ifndef _MSC_VER
    constexpr
#endif
    bool IsDebug() const { return false; }

#ifndef _MSC_VER
    constexpr
#endif
    bool IsError() const { return false; }

#ifndef _MSC_VER
    constexpr
#endif
    bool IsFatal() const { return false; }

#ifndef _MSC_VER
    constexpr
#endif
    bool IsInformation() const { return false; }

#ifndef _MSC_VER
    constexpr
#endif
    bool IsNotice() const { return false; }

#ifndef _MSC_VER
    constexpr
#endif
    bool IsTrace() const { return false; }

#ifndef _MSC_VER
    constexpr
#endif
    bool IsWarning() const { return false; }

    void Critical(std::string const& /*msg*/, int = 0) {}
    void Debug(std::string const& /*msg*/, int = 0) {}
    void Error(std::string const& /*msg*/, int = 0) {}
    void Fatal(std::string const& /*msg*/, int = 0) {}
    void Information(std::string const& /*msg*/, int = 0) {}
    void Notice(std::string const& /*msg*/, int = 0) {}
    void Trace(std::string const& /*msg*/, int = 0) {}
    void Warning(std::string const& /*msg*/, int = 0) {}
};

template <bool condition, typename LoggerImpl>
LoggerBridge<condition, LoggerImpl>::LoggerBridge(std::string const& loggerName, char const* file) :
    l(loggerName, file)
{
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::CreateLogger(std::string const& loggerName, std::string const& configFile)
{
    LoggerImpl::CreateLogger(loggerName, configFile);
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsCritical() const
{
    return l.IsCritical();
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsDebug() const
{
    return l.IsDebug();
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsError() const
{
    return l.IsError();
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsFatal() const
{
    return l.IsFatal();
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsInformation() const
{
    return l.IsInformation();
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsNotice() const
{
    return l.IsNotice();
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsTrace() const
{
    return l.IsTrace();
}

template <bool condition, typename LoggerImpl>
bool LoggerBridge<condition, LoggerImpl>::IsWarning() const
{
    return l.IsWarning();
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Critical(std::string const& msg)
{
    l.Critical(msg);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<DoesCritical<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Critical(const std::string& msg, int line)
{
    l.Critical(msg, line);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<!DoesCritical<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Critical(const std::string& msg, int)
{
    l.Critical(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Debug(std::string const& msg)
{
    l.Debug(msg);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<DoesDebug<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Debug(const std::string& msg, int line)
{
    l.Debug(msg, line);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<!DoesDebug<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Debug(const std::string& msg, int)
{
    l.Debug(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Error(std::string const& msg)
{
    l.Error(msg);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<DoesError<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Error(const std::string& msg, int line)
{
    l.Error(msg, line);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<!DoesError<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Error(const std::string& msg, int)
{
    l.Error(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Fatal(std::string const& msg)
{
    l.Fatal(msg);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<DoesFatal<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Fatal(const std::string& msg, int line)
{
    l.Fatal(msg, line);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<!DoesFatal<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Fatal(const std::string& msg, int)
{
    l.Fatal(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Information(std::string const& msg)
{
    l.Information(msg);
}

template <bool condition, typename LoggerImpl> template <typename LI>
typename std::enable_if<DoesInformation<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, LoggerImpl>::Information(const std::string& msg, int line)
{
    l.Information(msg, line);
}

template <bool condition, typename LoggerImpl> template <typename LI>
typename std::enable_if<!DoesInformation<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, LoggerImpl>::Information(const std::string& msg, int)
{
    l.Information(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Notice(std::string const& msg)
{
    l.Notice(msg);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<DoesNotice<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Notice(const std::string& msg, int line)
{
    l.Notice(msg, line);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<!DoesNotice<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Notice(const std::string& msg, int)
{
    l.Notice(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Trace(std::string const& msg)
{
    l.Trace(msg);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<DoesTrace<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Trace(const std::string& msg, int line)
{
    l.Trace(msg, line);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<!DoesTrace<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Trace(const std::string& msg, int)
{
    l.Trace(msg);
}

template <bool condition, typename LoggerImpl>
void LoggerBridge<condition, LoggerImpl>::Warning(std::string const& msg)
{
    l.Warning(msg);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<DoesWarning<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Warning(const std::string& msg, int line)
{
    l.Warning(msg, line);
}

template <bool condition, typename T> template <typename LI>
typename std::enable_if<!DoesWarning<LI, void, std::string const&, int>::Exist, void>::type
LoggerBridge<condition, T>::Warning(const std::string& msg, int)
{
    l.Warning(msg);
}

}
#endif // LoggerBridge_H
