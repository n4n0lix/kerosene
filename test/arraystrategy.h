#pragma once

#include "_global.h"
#include "bufferstrategy.h"
#include "bufferrange.h"


class ArrayStrategy : public BufferStrategy {
    void        _write(int index, vector<OBJECT>*);
    void        _remove(int index, int length);
    void        _resize(int oldCapacity, int newCapacity);

    map<TOKEN, BufferRange> _usedRanges;
    vector<BufferRange>     _freeRanges;
};