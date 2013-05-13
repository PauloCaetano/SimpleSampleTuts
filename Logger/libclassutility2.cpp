#include "libclassutility2.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassUtility2::LibClassUtility2(int pId) : id(pId), lcs(20+id)
{
    LibLogger l("lib");
    l.Debug("LibClassUtility2 ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassUtility2::~LibClassUtility2()
{
    LibLogger l("lib");
    l.Debug("LibClassUtility2 dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility2::DoSomething()
{
    LibLogger l("lib");
    l.Information("LibClassUtility2 DoSomething ID: " + Poco::NumberFormatter::format(id));
}

void LibClassUtility2::DoSomethingWithSupport()
{
    LibLogger l("lib");
    l.Information("LibClassUtility2 DoSomethingWithSupport ID: " + Poco::NumberFormatter::format(id));
    lcs.DoSomething();
}

}
