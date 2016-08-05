#pragma once

#include "_global.h"

class ListStrategy : public BufferStrategy {
    void        _write(int index, vector<OBJECT>*);
    void        _copy(int src, int dest, int length);
    void        _resize(int oldCapacity, int newCapacity);

    map<TOKEN, BufferRange> _usedRanges;
    BufferRange             _freeRange;
};