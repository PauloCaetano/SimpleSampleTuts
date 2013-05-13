#include "logger.h"

#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/AsyncChannel.h"
#include "Poco/Message.h"

#include <iostream>
using std::cout;
using std::endl;


namespace Lib {

Logger::Logger() : m_logger(Poco::Logger::get(""))
{
    cout << "Logger default ctor" << endl;
}

Logger::~Logger()
{
    cout << "Logger dtor" << endl;
}

void Logger::CreateLogger(std::string const& loggerName, std::string const& /*configFile*/)
{
    // IF THE LOGGER ALREADY EXISTS, WE DON'T NEED TO CREATE IT AGAIN
    if (Poco::Logger::has(loggerName) != nullptr)
    {
        return;
    }

    // THE FORMAT SPECS ARE AT THE END OF THIS FILE, COPIED FROM http://pocoproject.org/docs/
    Poco::FormattingChannel* frmt = new Poco::FormattingChannel(new
        Poco::PatternFormatter("%Y-%m-%d %H:%M:%S.%i [%p] [%N][%P][%T (%I)][%s][%U:%u] %t"));
    frmt->getFormatter()->setProperty("times", "local");

    Poco::FileChannel *fc = new Poco::FileChannel();
    fc->setProperty("times", "local");

    // FOR NOW, WE WON'T WORRY ABOUT GETTING THE PROPERTIES, WE'LL USE HARD-CODED DEFAULTS
    fc->setProperty("archive", "timestamp");
    fc->setProperty("compress", "true");
    fc->setProperty("purgeAge", "3 months");
    fc->setProperty("path", "log.txt");
    fc->setProperty("rotation", "daily");

    // USING AsyncChannel ON A SMALL CONSOLE PROGRAM LIKE THIS COULD MEAN THE PROGRAM ENDS
    // BEFORE THE LOGGING THREAD HAS HAD A CHANCE TO LOG ANYTHING, ESPECIALLY - AS IS THE
    // CASE HERE - WHEN THE LOGGER'S WORK IS MORE DEMANDING THAN THE PROGRAM'S
    frmt->setChannel(fc);
    //Poco::AsyncChannel *async = new Poco::AsyncChannel(frmt);
    Poco::Logger& logger = Poco::Logger::get(loggerName);
    logger.setLevel(Poco::Message::PRIO_TRACE);
    //logger.setChannel(async);
    logger.setChannel(frmt);
}

}

/*!
 *
    %s - message source
    %t - message text
    %l - message priority level (1 .. 7)
    %p - message priority (Fatal, Critical, Error, Warning, Notice, Information, Debug, Trace)
    %q - abbreviated message priority (F, C, E, W, N, I, D, T)
    %P - message process identifier
    %T - message thread name
    %I - message thread identifier (numeric)
    %N - node or host name
    %U - message source file path (empty string if not set)
    %u - message source line number (0 if not set)
    %w - message date/time abbreviated weekday (Mon, Tue, ...)
    %W - message date/time full weekday (Monday, Tuesday, ...)
    %b - message date/time abbreviated month (Jan, Feb, ...)
    %B - message date/time full month (January, February, ...)
    %d - message date/time zero-padded day of month (01 .. 31)
    %e - message date/time day of month (1 .. 31)
    %f - message date/time space-padded day of month ( 1 .. 31)
    %m - message date/time zero-padded month (01 .. 12)
    %n - message date/time month (1 .. 12)
    %o - message date/time space-padded month ( 1 .. 12)
    %y - message date/time year without century (70)
    %Y - message date/time year with century (1970)
    %H - message date/time hour (00 .. 23)
    %h - message date/time hour (00 .. 12)
    %a - message date/time am/pm
    %A - message date/time AM/PM
    %M - message date/time minute (00 .. 59)
    %S - message date/time second (00 .. 59)
    %i - message date/time millisecond (000 .. 999)
    %c - message date/time centisecond (0 .. 9)
    %F - message date/time fractional seconds/microseconds (000000 - 999999)
    %z - time zone differential in ISO 8601 format (Z or +NN.NN)
    %Z - time zone differential in RFC format (GMT or +NNNN)
    %E - epoch time (UTC, seconds since midnight, January 1, 1970)
    %[name] - the value of the message parameter with the given name
    %% - percent sign
*/
