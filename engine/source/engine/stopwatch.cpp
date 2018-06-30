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

// Resets the stopwatch to 0.
void StopWatch::start()
{
    tick();
}

// Returns the amount of elapsed ms since last start()/tick()
// and resets the stopwatch to 0.
uint64 StopWatch::tick()
{
    uint64 tickCurrent = current_ms();
    uint64 tickDuration = tickCurrent - _lastTick;
    _lastTick = tickCurrent;

    return tickDuration;
}

// Returns the amount of elapsed ms since last start()/tick()
// WITHOUT resetting the stopwatch.
uint64 StopWatch::elapsed()
{
    return current_ms() - _lastTick;
}

bool StopWatch::wait_until( uint64 t )
{
  if (elapsed() > t) {
    start();
    return true;
  }

  return false;
}

ENGINE_NAMESPACE_END

