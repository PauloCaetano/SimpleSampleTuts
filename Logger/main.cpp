#include "libclassmain.h"
#include "lib_logger.h"

#include "Poco/Logger.h"

#include <string>
using std::string;

int main(int /*argc*/, char **/*argv[]*/)
{
    // WE'LL NEED TO DEFINE SOME POINT IN OUR LIB FOR THIS INITIALIZATION
    LibLogger::CreateLogger("lib", "");

    LibLogger l("lib");
    l.Information("Start");

    Lib::LibClassMain l1(1), l2(2);

    l1.DoSomething();
    l2.DoSomething();

    l1.DoSomethingMoreElaborate1();
    l2.DoSomethingMoreElaborate2();

    l1.GoOverboard1();
    l2.GoOverboard2();

    l.Information("End");
}
