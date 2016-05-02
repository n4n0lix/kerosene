#pragma once

#include "logger.h"

template <class T>
class A {
public:
    void test() { LOGGER.log(Level::DEBUG) << "Hello :)" << endl; }
private:
    static Logger LOGGER;
};

template <class T>
Logger A<T>::LOGGER = Logger("A", Level::DEBUG);