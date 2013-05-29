/*!
 *  Implementing logging in a library.
 *
 *  1. No logging. The lib classes perform no logging of their activity and logging code is excluded from the
 *     the build, via #define.
 *
 *  2. Default logging. The lib classes log their activity. The log settings will be defined in a default
 *     .properties file, that must reside in the same directory as the application (not the lib itself).
 *     This use the default logging implementation, and the user can't change it.
 *
 *  2.1. Where will we place the initialization of the logger, i.e., reading the .properties file?
 *
 *  3. User-defined logging. We will only support this at build-time, and not at runtime.
 *
 *  3.1. We can have a template Logger class, with parameters for: Logger implementation, reading settings,
 *       creating client/operation IDs
 *
 *  4. Logger class or logging functions? Do we need to keep state of our own - e.g., ID generation data?
 *
 *  LibClassMain - Lib class that is instantiated in the client code.
 *  LibClassUtility1, LibClassUtility2 - Lib classes used by LibClassMain.
 *  LibClassSupport - Lib class used by other lib classes.
 *
 *  Logger - Our lib's logger class implementation, used in default logging. Because our default implementation
 *      will be Poco's logger, we'll use its interface as a model.
 *  LoggerBridge - Our logger's interface class, it'll isolate our code from the actual logger implementation.
 *
 *  The central point of our mechanism is lib_logger.h. This file will include the headers for LoggerBridge
 *  (the template class) and the implementation class(es), and create a typedef to use in the whole library.
 *  So, our own lib_logger.h will implement point 2. If the user wants to supply a different logging
 *  implementation, all he has to do is replace our lib_logger.h with his own, and supply his own typedef.
 *  Provided the interface remains the same, we should have no problem.
 *
 *  As an example, we've created a different implementation, that logs to cout (LoggerCout). We've just changed
 *  lib_logger.h, and everything worked. In fact, we probably don't need the template class, but we'll keep it
 *  for now.
 *
 *  ToDo: try a classless implementation.
 **/

#include "libclassmain.h"
#include "lib_logger.h"

#include "Poco/Logger.h"

#include <string>
using std::string;

int main(int /*argc*/, char **/*argv[]*/)
{
    // WE'LL NEED TO DEFINE SOME POINT IN OUR LIB FOR THIS INITIALIZATION
    LibLogger::CreateLogger("lib", "");

    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("Start");

    Lib::LibClassMain l1(1), l2(2);

    l1.DoSomething();
    l2.DoSomething();

    l1.DoSomethingMoreElaborate1();
    l2.DoSomethingMoreElaborate2();

    l1.GoOverboard1();
    l2.GoOverboard2();

    PCLIB_LOGGER_INFORMATION_CHECK("End");
}
