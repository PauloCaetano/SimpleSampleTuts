#include "libclassmain.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassMain::LibClassMain(int pId) : id(pId), lcu1(id), lcu2(id)
{
    LibLogger l("lib");
    l.Debug("LibClassMain ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassMain::~LibClassMain()
{
    LibLogger l("lib");
    l.Debug("LibClassMain dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassMain::DoSomething()
{
    LibLogger l("lib");
    l.Information("LibClassMain DoSomething ID: " + Poco::NumberFormatter::format(id));
}

void LibClassMain::DoSomethingMoreElaborate1()
{
    LibLogger l("lib");
    l.Information("LibClassMain DoSomethingMoreElaborate1 ID: " + Poco::NumberFormatter::format(id));
    lcu1.DoSomething();
}

void LibClassMain::DoSomethingMoreElaborate2()
{
    LibLogger l("lib");
    l.Information("LibClassMain DoSomethingMoreElaborate2 ID: " + Poco::NumberFormatter::format(id));
    lcu2.DoSomething();
}

void LibClassMain::GoOverboard1()
{
    LibLogger l("lib");
    l.Information("LibClassMain GoOverboard1 ID: " + Poco::NumberFormatter::format(id));
    lcu1.DoSomethingWithSupport();
}

void LibClassMain::GoOverboard2()
{
    LibLogger l("lib");
    l.Information("LibClassMain GoOverboard2 ID: " + Poco::NumberFormatter::format(id));
    lcu2.DoSomethingWithSupport();
}

}
