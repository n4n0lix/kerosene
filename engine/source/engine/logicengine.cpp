// Header
#include "logicengine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void LogicEngine::on_start()
{

}

void LogicEngine::on_tick_start()
{
    _snapshot.clear();
    for ( auto entity : _entities ) {
        unique<Entity>  copy = make_unique<Entity>();

        entitySys.create_snapshot_full( *copy, *entity );
        controllableSys.create_snapshot_full( *copy, *entity );

        _snapshot.emplace_back( std::move( copy ) );
    }
}

void LogicEngine::on_update()
{
    for ( auto e : _entities ) {
        Entity& entity = *e;

        entitySys.update( entity );
        controllableSys.update( entity );
    }
}

void LogicEngine::on_shutdown()
{
    _snapshot.clear();
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
    wEntity->id = ENTITY_ID_GENERATOR.new_id();

    return wEntity;
}

owner<Entity> LogicEngine::remove_entity( weak<Entity> wEntity )
{
    Guard( wEntity.ptr_is_usable() ) return nullptr;

    owner<Entity> oEntity = extract_owner( _entityOwners, wEntity );
    _entities.erase( std::remove( _entities.begin(), _entities.end(), wEntity ) );
    
    return oEntity;
}

vector<weak<Entity>>& LogicEngine::get_entities()
{
    return _entities;
}

//uint64 LogicEngine::ticks_elapsed_since( uint64 t )
//{
//    // 1# No overflow
//    if ( _tick > _lastTick ) {
//        return _tick - _lastTick;
//    }
//    // 2# Overflow
//    else {
//        //   (Dist from WRAP to _tick) 
//        // + (Dist from WRAP to _lasttick) 
//        // + 1 (for the WRAP)
//        return _tick + (MAX( _tick ) - _lastTick) + 1;
//    }
//}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

IDGen LogicEngine::ENTITY_ID_GENERATOR = IDGen();

ENGINE_NAMESPACE_END
