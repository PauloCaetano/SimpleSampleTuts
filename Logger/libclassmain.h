#ifndef LIBCLASSMAIN_H
#define LIBCLASSMAIN_H

#include "libclassutility1.h"
#include "libclassutility2.h"

namespace Lib {

class LibClassMain
{
public:
    explicit LibClassMain(int pId);
    ~LibClassMain();

    void DoSomething();
    void DoSomethingMoreElaborate1();
    void DoSomethingMoreElaborate2();
    void GoOverboard1();
    void GoOverboard2();

private:
    int id;
    LibClassUtility1 lcu1;
    LibClassUtility2 lcu2;
};

}

#endif // LIBCLASSMAIN_H
