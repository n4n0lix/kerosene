#pragma once

#include "_global.h"

template<class OBJECT>
class BufferProperties {

public:
    BufferProperties(uint32 objCapacity) () 
    {
        _atomCapacity = objCapacity * sizeof(OBJECT);
    }

    uint32 object_size()        { return sizeof(OBJECT); }
    uint32 object_capacity()    { return _atomCapacity / sizeof(OBJECT); }

    uint32 atom_capacity()      { return _atomCapacity; }

private:
    uint32 _atomCapacity;
};