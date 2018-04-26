#ifndef TESTDLL_H
#define TESTDLL_H

#define TESTDLL_EXPORT __declspec(dllexport)
#ifdef TESTDLL_EXPORT
#else
#define NTXQH_PLUGINSHARED_EXPORT __declspec(dllimport)
#endif

class TESTDLL_EXPORT TestDll
{
public:
    TestDll();
    virtual~TestDll();
    virtual void helloWorld(); //类成员函数
private:


};
extern "C" TESTDLL_EXPORT TestDll* getTestDll(); //获取类TestDll的对象
#endif // TESTDLL_H
