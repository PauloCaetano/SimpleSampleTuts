#ifndef LIBCLASSUTILITY1_H
#define LIBCLASSUTILITY1_H

#include "libclasssupport.h"

namespace Lib {

class LibClassUtility1
{
public:
    explicit LibClassUtility1(int pId);
    ~LibClassUtility1();

    void DoSomething();
    void DoSomethingWithSupport();
private:
    int id;
    LibClassSupport lcs;
};

}

#endif // LIBCLASSUTILITY1_H
