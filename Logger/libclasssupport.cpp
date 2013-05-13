#include "libclasssupport.h"
#include "lib_logger.h"

#include "Poco/NumberFormatter.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Lib {

LibClassSupport::LibClassSupport(int pId) : id(pId)
{
    LibLogger l("lib");
    l.Debug("LibClassSupport ctor ID: " + Poco::NumberFormatter::format(id));
}

LibClassSupport::~LibClassSupport()
{
    LibLogger l("lib");
    l.Debug("LibClassSupport dtor ID: " + Poco::NumberFormatter::format(id));
}

void LibClassSupport::DoSomething()
{
    LibLogger l("lib");
    l.Information("LibClassSupport DoSomething ID: " + Poco::NumberFormatter::format(id));
}

}
