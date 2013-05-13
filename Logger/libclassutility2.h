#ifndef LIBCLASSUTILITY2_H
#define LIBCLASSUTILITY2_H

#include "libclasssupport.h"

namespace Lib {

class LibClassUtility2
{
public:
    explicit LibClassUtility2(int pId);
    ~LibClassUtility2();

    void DoSomething();
    void DoSomethingWithSupport();
private:
    int id;
    LibClassSupport lcs;
};

}

#endif // LIBCLASSUTILITY2_H
