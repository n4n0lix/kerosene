#include "stdafx.h"
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
    //_snapshot.clear();
    //for ( auto entity : _entities ) {
    //    unique<Entity>  copy = make_unique<Entity>();

    //    //entitySys.create_snapshot_full( *copy, *entity );
    //    //controllableSys.create_snapshot_full( *copy, *entity );

    //    _snapshot.emplace_back( std::move( copy ) );
    //}
}

void LogicEngine::on_update( float delta )
{
  for ( auto& c : CTransform::get_all_components().values() )
    c.update(delta);

  for ( auto& c : CControllable::get_all_components().values() )
    c.update( delta );

  for ( auto& c : CTilemapLogic::get_all_components().values() )
    c.update( delta );
}

void LogicEngine::on_shutdown()
{

}

void LogicEngine::on_gamestate_end()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



ENGINE_NAMESPACE_END
