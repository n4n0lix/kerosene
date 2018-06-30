#include "stdafx.h"
#include "tilemap_spawner.h"

Entity Tilemap_Spawner::Spawn( LogicEngine& logic, weak<RenderEngine> rendering, weak<InputEngine> input, weak<Scene> mainScene )
{
    // LOGIC
    Entity wEntity = Entity::New();
    wEntity.add<CTransform>();
   
    CTilemapLogic& data = wEntity.add<CTilemapLogic>();
    data.tileWidth = 12.0f;
    data.tileHeight = 12.0f;
    data.reshape( 16, 16 );
    for(uint32 y = 0; y < 16; y++ )
        for ( uint32 x = 0; x < 16; x++ ) {
            auto rnd = 0 + (rand() * (int)(2) / RAND_MAX);
            data.set_tile( x, y, rnd );
        }


    // INPUT

    // RENDERING
    if ( rendering && mainScene ) {
        auto oTileset = make_owner<Tileset>( "res/textures/tileset.png", 16, 16 );
        auto wTileset = rendering->add_resource<Tileset>( "tileset", std::move( oTileset ) );

        auto r = mainScene->add_renderer<TilemapRenderer>( wTileset, wEntity );

    }

    return wEntity;
}