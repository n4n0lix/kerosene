#include "stdafx.h"
#include "tilemap_spawner.h"

weak<Entity> Tilemap_Spawner::Spawn( LogicEngine& logic, weak<RenderEngine> rendering, weak<InputEngine> input, weak<Scene> mainScene )
{
    weak<Entity> tilemap = nullptr;

    // LOGIC
    tilemap = logic.add_entity( make_owner<Entity>() );
    tilemap->add<has_transform>();
    TilemapLogic& data = tilemap->add<TilemapLogic>();

    data.tileWidth = 12.0f;
    data.tileHeight = 12.0f;
    data.reshape( 16, 16 );


    // INPUT

    // RENDERING
    if ( rendering && mainScene ) {
        auto rCfg = TilemapRenderer::Config( {
            /*            entity = */ tilemap,
            /*       textureName = */ "res/textures/dev/tile.png",
            /*  tilesetTileWidth = */ 16,
            /* tilesetTileHeight = */ 16
        } );

        mainScene->add_renderer<TilemapRenderer>( rCfg );
    }

    return tilemap;
}