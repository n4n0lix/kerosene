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
    // 1# Count ticks
    _lastTick = _tick;
    _tick++;

    // 2# Take a snapshot
    _snapshot.clear();
    for ( auto entity : _entities ) {
        Entity copy = *(entity.get());
        _snapshot.push_back( std::move( copy ) );
    }

    // Entities get copied here, which means if the copy gets destructed,
    // the uid gets released, although there is still a valid entity existing (the original)
    // This can be fixed by giving custom destructor to owner
}

void LogicEngine::on_shutdown()
{

}

uint64 LogicEngine::current_tick()
{
    return _tick;
}

void LogicEngine::on_gamestate_end()
{
    _entities.clear();
    _entityOwners.clear();
}

weak<Entity>  LogicEngine::add_entity( owner<Entity> oEntity )
{
    Guard( oEntity != nullptr ) return nullptr;

    weak<Entity> wEntity = oEntity.get_non_owner();

    _entities.push_back( wEntity );
    _entityOwners.emplace_back( std::move( oEntity ) );
    wEntity->uid = ENTITY_ID_GENERATOR.new_id();

    return wEntity;
}

owner<Entity> LogicEngine::remove_entity( weak<Entity> wEntity )
{
    Guard( wEntity.ptr_is_usable() ) return nullptr;

    owner<Entity> oEntity = extract_owner( _entityOwners, wEntity );
    _entities.erase( std::remove( _entities.begin(), _entities.end(), wEntity ) );
    ENTITY_ID_GENERATOR.release_id( oEntity->uid );
    
    return oEntity;
}

vector<weak<Entity>>& LogicEngine::get_entities()
{
    return _entities;
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

IDGen LogicEngine::ENTITY_ID_GENERATOR = IDGen();

ENGINE_NAMESPACE_END
