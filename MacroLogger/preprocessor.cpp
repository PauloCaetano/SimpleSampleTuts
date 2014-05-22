#include "log_interface_type.h"

// Experiment setting LOG_IMPLEMENTATION and LOG_DESTINATION to different values.
// If you use a different logging lib that supplies a stream interface, create
// a file like boost_log.h/poco_log.h, implement the macros, and use it
#define LOG_IMPLEMENTATION_BOOST 1
#define LOG_IMPLEMENTATION_POCO 2
#define LOG_IMPLEMENTATION LOG_IMPLEMENTATION_BOOST
#define LOG_DESTINATION_CONSOLE 1
#define LOG_DESTINATION_FILE 2
#define LOG_DESTINATION LOG_DESTINATION_FILE

#if LOG_IMPLEMENTATION == LOG_IMPLEMENTATION_BOOST
#include "boost_log.h"
#endif
#if LOG_IMPLEMENTATION == LOG_IMPLEMENTATION_POCO
#include "poco_log.h"
#endif

#if LOG_DESTINATION == LOG_DESTINATION_CONSOLE
#define CREATE_LOGGER() CreateConsoleLogger()
#endif
#if LOG_DESTINATION == LOG_DESTINATION_FILE
#define CREATE_LOGGER() CreateFileLogger()
#endif

#include <algorithm>
using std::copy;
#include <iostream>
using std::ostream;
#include <iterator>
using std::ostream_iterator;
#include <string>
using std::string;
#include <vector>
using std::vector;

#if LOG_IMPLEMENTATION == LOG_IMPLEMENTATION_POCO
void CreateConsoleLogger()
{
    Poco::FormattingChannel* frmt = new Poco::FormattingChannel(new
        Poco::PatternFormatter("%Y-%m-%d %H:%M:%S.%i [%p] [%N][%P][%T (%I)][%s][%U:%u] %t"));
    frmt->getFormatter()->setProperty("times", "local");

    Poco::ConsoleChannel *fc = new Poco::ConsoleChannel();

    frmt->setChannel(fc);
    Poco::Logger& logger = Poco::Logger::get("TestLog");
    logger.setLevel(Poco::Message::PRIO_TRACE);
    logger.setChannel(frmt);
}

void CreateFileLogger()
{
    Poco::FormattingChannel* frmt = new Poco::FormattingChannel(new
        Poco::PatternFormatter("%Y-%m-%d %H:%M:%S.%i [%p] [%N][%P][%T (%I)][%s][%U:%u] %t"));
    frmt->getFormatter()->setProperty("times", "local");

    Poco::FileChannel *fc = new Poco::FileChannel();
    fc->setProperty("times", "local");

    fc->setProperty("archive", "timestamp");
    fc->setProperty("compress", "true");
    fc->setProperty("purgeAge", "3 months");
    fc->setProperty("path", "log.txt");
    fc->setProperty("rotation", "daily");

    frmt->setChannel(fc);
    Poco::Logger& logger = Poco::Logger::get("TestLog");
    logger.setLevel(Poco::Message::PRIO_TRACE);
    logger.setChannel(frmt);
}

#endif

#if LOG_IMPLEMENTATION == LOG_IMPLEMENTATION_BOOST

// On Poco, using operator<<(), it's up to us to include __FILE__ and __LINE__ in
// the output; we're using the message for that. We'll use the same "solution"
// with Boost.
void CreateConsoleLogger()
{
    // Timestamp, priority, hostname, pid, tid, message source, file:line, text
    logging::add_console_log(std::clog,
        keywords::format = (
            expr::stream <<
            expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
            " [" << boost::log::trivial::severity << "] " << expr::smessage
        )
    );

    // This is how we add just the timestamp
    auto core = logging::core::get();
    core->add_global_attribute("TimeStamp", attrs::local_clock());

    // This only works if we use a severity_logger. If we use a normal logger,
    // no records pass the filter.
    core->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
}

void CreateFileLogger()
{
    // Timestamp, priority, hostname, pid, tid, message source, file:line, text
    logging::add_file_log(
        keywords::file_name = "myapp_%Y%m%d.log",
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = (
            expr::stream <<
            expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
            " [" << boost::log::trivial::severity << "] " << expr::smessage
        )
    );

    // This is how we add just the timestamp
    auto core = logging::core::get();
    core->add_global_attribute("TimeStamp", attrs::local_clock());

    // This only works if we use a severity_logger. If we use a normal logger,
    // no records pass the filter.
    core->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
}

#endif

struct WeaponList
{
    WeaponList()
        : vec{"Fear", "Surprise", "Ruthless Efficiency", "An Almost Fanatical Devotion to the Pope",
        "Nice Red Uniforms"} {}
    vector<string> vec;
};

ostream& operator<<(ostream& os, WeaponList const& wl)
{
    copy(wl.vec.cbegin(), wl.vec.cend(), ostream_iterator<string>(os, "\n"));
    return os;
}

struct Farm
{
    float Trouble() { return 3.2; }
};

int GetValue()
{
    return 42;
}

int main()
{
    CREATE_LOGGER();

    PCBLUESY__GETLOGGER("TestLog");

    Farm mill;
    WeaponList chiefWeapons;

    PCBLUESY__LOG(PCBLUESY__ERROR, "Blimey! I didn't expect the Spanish Inquisition ERROR!",
        mill.Trouble(), chiefWeapons, GetValue());
    PCBLUESY__LOG(PCBLUESY__DEBUG, "Blimey! I didn't expect the Spanish Inquisition DEBUG!",
        mill.Trouble(), chiefWeapons, GetValue());
    PCBLUESY__LOG(PCBLUESY__INFO, "Blimey! I didn't expect the Spanish Inquisition INFO!",
        mill.Trouble(), chiefWeapons, GetValue());
}
