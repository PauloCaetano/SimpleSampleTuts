#include "libclassutility2.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassUtility2::LibClassUtility2(int pId) : id(pId), lcs(20+id)
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassUtility2 ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassUtility2::~LibClassUtility2()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassUtility2 dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility2::DoSomething()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassUtility2 DoSomething ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility2::DoSomethingWithSupport()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassUtility2 DoSomethingWithSupport ID: " + Poco::NumberFormatter::format(id));
    lcs.DoSomething();
}

}
