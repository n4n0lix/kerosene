#pragma once

#include <string>
        using std::string;

class TestClass
{
public:
    virtual int    run() = 0;
    virtual string name() = 0;
    virtual string className() = 0;
    int exec() {
        return run();
    }
};

#define BEHAVIOUR( CLASS, NAME )                            \
  class NAME : public TestClass                             \
  {                                                         \
  public:                                                   \
    NAME##() { registry.reg(this); }                        \
    virtual int run() override;                             \
    virtual string name() override;                         \
    virtual string className() override;                    \
  } NAME##Instance;                                         \
  string NAME##::name() { return #NAME##; }                 \
  string NAME##::className() { return #CLASS##; }           \
  int NAME##::run() {

#define END return 0; }