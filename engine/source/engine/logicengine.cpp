// Header
#include "logicengine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

LogicEngine::LogicEngine()
{

}

void LogicEngine::on_start()
{
    _tick = 0;
    _lastTick = 0;
}

void LogicEngine::on_update()
{
    _lastTick = _tick;
    _tick++;
}

void LogicEngine::on_shutdown()
{

}

uint64 LogicEngine::current_tick()
{
    return _tick;
}

uint64 LogicEngine::ticks_elapsed_since( uint64 t )
{
    // 1# No overflow
    if ( _tick > _lastTick ) {
        return _tick - _lastTick;
    }
    // 2# Overflow
    else {
        //   (Dist from WRAP to _tick) 
        // + (Dist from WRAP to _lasttick) 
        // + 1 (for the WRAP)
        return _tick + (MAX( _tick ) - _lastTick) + 1;
    }
}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
