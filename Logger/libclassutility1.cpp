#include "libclassutility1.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassUtility1::LibClassUtility1(int pId) : id(pId), lcs(10+id)
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassUtility1 ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassUtility1::~LibClassUtility1()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassUtility1 dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility1::DoSomething()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassUtility1 DoSomething ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility1::DoSomethingWithSupport()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassUtility1 DoSomethingWithSupport ID: " + Poco::NumberFormatter::format(id));
    lcs.DoSomething();
}

}
