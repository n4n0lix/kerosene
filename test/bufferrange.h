#pragma once

#include "_global.h"

class BufferRange {

public:
    BufferRange(uint32 index, uint32 length) : _index(index), _length(length) {}

    uint32 index()          { return _index; }
    uint32 last_index()     { return _index + _length - 1; }
    
    uint32 length()         { return _length; }

private:
    uint32 _index;
    uint32 _length;
};