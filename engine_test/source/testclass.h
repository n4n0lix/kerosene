#pragma once

#include <string>
        using std::string;

class TestClass
{
public:
    virtual int    run() = 0;
    virtual string name() = 0;

    int exec() {
        return run();
    }
};

#define BEHAVIOUR( NAME )                               \
  class NAME : public TestClass                         \
  {                                                     \
  public:                                               \
    NAME##() { registry.reg(this); }                    \
    virtual int run() override;                        \
    virtual string name() override;                     \
  } NAME##Instance;                                     \
  string NAME##::name() { return #NAME##; }             \
  int NAME##::run()