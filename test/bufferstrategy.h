#pragma once

#include "_global.h"
#include "bufferrange.h"

template<class OBJECT, class TOKEN>
class BufferStrategy {

    BufferRange write(TOKEN, vector<OBJECT>*);
    void        remove(TOKEN);

};