#ifndef LIBCLASSSUPPORT_H
#define LIBCLASSSUPPORT_H

namespace Lib {

class LibClassSupport
{
public:
    explicit LibClassSupport(int pId);
    ~LibClassSupport();

    void DoSomething();
private:
    int id;
};

}
#endif // LIBCLASSSUPPORT_H
