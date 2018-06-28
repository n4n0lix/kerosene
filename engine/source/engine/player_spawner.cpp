#include "stdafx.h"
#include "player_spawner.h"

weak<Entity> Player_Spawner::Spawn( LogicEngine& logic, weak<RenderEngine> rendering, weak<InputEngine> input, weak<Scene> mainScene )
{
    weak<Entity> player = nullptr;

    // LOGIC
    player = logic.add_entity( make_owner<Entity>() );
    player->add<has_transform>();
    Controllable& ctrl = player->add<Controllable>();

    ctrl.name = "Player";
    ctrl.moveSpeed = 100;

    // INPUT
    if ( input ) {
        input->add_local_controller( 10, make_owner<PlayerController>( player ) );
    }

    // RENDERING
    if ( rendering && mainScene ) {
        auto texture = rendering->get_texture( "res/textures/dev/test_char.png" );

        auto rCfg = SpriteRenderer::Config( {
            /*  anchor = */{ 0, 0 },
            /*    size = */{ (float)texture->get_width(), (float)texture->get_height() },
            /* texture = */ texture,
            /*  entity = */ player
        } );

        auto renderer = mainScene->add_renderer<SpriteRenderer>( rCfg );
    }

    return player;
}