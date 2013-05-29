#include "libclassmain.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassMain::LibClassMain(int pId) : id(pId), lcu1(id), lcu2(id)
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassMain ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassMain::~LibClassMain()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_DEBUG_CHECK("LibClassMain dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassMain::DoSomething()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassMain DoSomething ID: " + Poco::NumberFormatter::format(id));
}

void LibClassMain::DoSomethingMoreElaborate1()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassMain DoSomethingMoreElaborate1 ID: " + Poco::NumberFormatter::format(id));
    lcu1.DoSomething();
}

void LibClassMain::DoSomethingMoreElaborate2()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassMain DoSomethingMoreElaborate2 ID: " + Poco::NumberFormatter::format(id));
    lcu2.DoSomething();
}

void LibClassMain::GoOverboard1()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassMain GoOverboard1 ID: " + Poco::NumberFormatter::format(id));
    lcu1.DoSomethingWithSupport();
}

void LibClassMain::GoOverboard2()
{
    PCLIB_GETLOGGER("lib");
    PCLIB_LOGGER_INFORMATION_CHECK("LibClassMain GoOverboard2 ID: " + Poco::NumberFormatter::format(id));
    lcu2.DoSomethingWithSupport();
}

}
