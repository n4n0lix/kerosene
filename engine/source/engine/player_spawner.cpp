#include "stdafx.h"
#include "player_spawner.h"

weak<Entity> Player_Spawner::Spawn( LogicEngine& logic, weak<RenderEngine> rendering, weak<InputEngine> input, weak<Scene> mainScene )
{
    weak<Entity> player = nullptr;

    player = logic.add_entity( make_owner<Entity>() );
    player->add_component<Controllable>( );

    // INPUT
    if ( input ) {
        //input->add_local_controller( 10, make_owner<PlayerController>( player ) );
    }

    if ( rendering && mainScene ) {
        auto texture = rendering->get_texture( "res/textures/dev/test_char.png" );

        SpriteRenderer::Config rCfg = { { 0,0 },{ 1,1 }, texture, player };

        auto renderer = mainScene->add_renderer<SpriteRenderer>( rCfg );
    }

    return player;
}
