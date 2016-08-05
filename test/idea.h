#pragma once

#include <vector> 
using std::vector;

#include <map>
using std::map;

class OBJECT {};
class TOKEN {};

// Responsibility: Describes a buffer range
class BufferRange {
    int index;
    int length;
};

class BufferProperties {
    int atomCapacity;
    int objectSize;
};

// Responsibility: Basic interface for adding and removing objects from a buffer
class Buffer {
    TOKEN   write(vector<OBJECT>*);
    void    remove(TOKEN);
};

// Responsibility: How the objects are stored in the buffer
class BufferStrategy {
    BufferRange write(TOKEN, vector<OBJECT>*);
    void        remove(TOKEN);
};

// Responsibility: Greedy packing
class ArrayStrategy : public BufferStrategy {
    void        _write(int index, vector<OBJECT>*);
    void        _remove(int index, int length);
    void        _resize(int oldCapacity, int newCapacity);

    map<TOKEN, BufferRange> _usedRanges;
    vector<BufferRange>     _freeRanges;
};

// Responsibility: Continously packing
class ListStrategy : public BufferStrategy {
    void        _write(int index, vector<OBJECT>*);
    void        _copy(int src, int dest, int length);
    void        _resize(int oldCapacity, int newCapacity);

    map<TOKEN, BufferRange> _usedRanges;
    BufferRange             _freeRange;
};

// Responsibility: Buffer interaction via transaction bulking
class TransactionBucket {
    void        commit();
    TOKEN       write(vector<OBJECT>*);
    void        remove(TOKEN);

    void        commit_write(TOKEN, vector<OBJECT>*);
    void        commit_remove(TOKEN);
};