#include "libclassutility1.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassUtility1::LibClassUtility1(int pId) : id(pId), lcs(10+id)
{
    LibLogger l("lib");
    l.Debug("LibClassUtility1 ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassUtility1::~LibClassUtility1()
{
    LibLogger l("lib");
    l.Debug("LibClassUtility1 dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility1::DoSomething()
{
    LibLogger l("lib");
    l.Information("LibClassUtility1 DoSomething ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility1::DoSomethingWithSupport()
{
    LibLogger l("lib");
    l.Information("LibClassUtility1 DoSomethingWithSupport ID: " + Poco::NumberFormatter::format(id));
    lcs.DoSomething();
}

}
