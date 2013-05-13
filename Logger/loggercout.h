#ifndef LOGGERCOUT_H
#define LOGGERCOUT_H

#include <iostream>
#include <string>

namespace SomethingElse
{

class LoggerCout
{
public:
    explicit LoggerCout(std::string const& /*loggerName*/) {}

    static void CreateLogger(std::string const& /*loggerName*/, std::string const& /*configFile*/) {}

    void Critical(std::string const& msg) { print("Critical - " + msg); }
    void Debug(std::string const& msg) { print("Debug - " + msg); }
    void Error(std::string const& msg) { print("Error - " + msg); }
    void Fatal(std::string const& msg) { print("Fatal - " + msg); }
    void Information(std::string const& msg) { print("Information - " + msg); }
    void Notice(std::string const& msg) { print("Notice - " + msg); }
    void Trace(std::string const& msg) { print("Trace - " + msg); }
    void Warning(std::string const& msg) { print("Warning - " + msg); }
private:
    void print(std::string const& msg) { std::cout << msg << std::endl; }
};

}

#endif // LOGGERCOUT_H
