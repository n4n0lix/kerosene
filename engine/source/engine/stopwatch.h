#pragma once

// Std-Includes
#include <chrono>

// Other Includes

// Internal Includes
#include "_global.h"

#include "logger.h"

ENGINE_NAMESPACE_BEGIN

class StopWatch
{
public:
    static uint64 current_ms();

    StopWatch();

    void     start();
    uint64   tick();
    uint64   elapsed();
    bool     wait_until(uint64);

private:
    uint64 _lastTick;

};

ENGINE_NAMESPACE_END
