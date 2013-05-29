#include "libclasssupport.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassSupport::LibClassSupport(int pId) : id(pId)
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassSupport ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassSupport::~LibClassSupport()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassSupport dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassSupport::DoSomething()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassSupport DoSomething ID: " + Poco::NumberFormatter::format(id));
}

}
