#include "stdafx.h"
#include "stopwatch.h"

ENGINE_NAMESPACE_BEGIN

uint64 StopWatch::current_ms()
{
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
        ).count();
}

StopWatch::StopWatch() : _lastTick( 0 )
{
    start();
}

void StopWatch::start()
{
    tick();
}

uint64 StopWatch::tick()
{
    uint64 tickCurrent = current_ms();
    uint64 tickDuration = tickCurrent - _lastTick;
    _lastTick = tickCurrent;

    return tickDuration;
}

ENGINE_NAMESPACE_END

