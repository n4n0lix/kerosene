#include "stdafx.h"
#include "testgamestate.h"

using namespace ENGINE_NAMESPACE;

TestGameState::~TestGameState()
{

}

void TestGameState::on_start()
{
    auto rendering = get_renderengine();

    // RENDER
    if ( rendering ) {
        rendering->get_window()->set_title( "kerosene - Test" );

        _mainScene  = rendering->add_scene<Scene>();
        _mainCamera = _mainScene->add_camera<Camera2D>();
        _mainCamera->set_zoom( 4 );
        _player = spawn_player( _mainScene );

        _uiScene = rendering->add_scene<Scene>();
        _uiCamera = _uiScene->add_camera<Camera2D>();
        _uiCamera->set_zoom( 4 );
        _ui = spawn_ui( _uiScene );
    }


}

void TestGameState::on_update()
{
    auto inputengine = get_inputengine();

    // INPUT
    if ( inputengine ) {
        vector<KeyEvent>& keys = get_inputengine()->get_keyevents();

        for ( auto& event : keys) {
            if ( event.is_consumed() ) continue;

            if ( event.key() == Key::Escape ) {
                set_status( GameStateStatus::FINISHED );
                event.consume();
            }

            if ( _player ) {
                if ( event.key() == Key::Q ) {
                    _player->scale.x += 0.1f;
                    event.consume();
                }
                else if ( event.key() == Key::E ) {
                    _player->scale.x -= 0.1f;
                    event.consume();
                }
            }

            if ( _mainCamera && event.state_changed() ) {
                Vector3f camTarget = _mainCamera->get_target();

                if ( event.key() == Key::W ) {
                    moveCamUp = event.pressed();
                    event.consume();
                }
                else if ( event.key() == Key::S ) {
                    moveCamDown = event.pressed();
                    event.consume();
                }
                else if ( event.key() == Key::A ) {
                    moveCamLeft = event.pressed();
                    event.consume();
                }
                else if ( event.key() == Key::D ) {
                    moveCamRight  = event.pressed();
                    event.consume();
                }
            }
        }
    }

    // Main Camera Update
    if ( moveCamUp || moveCamDown || moveCamLeft || moveCamRight ) {
        Vector3f target = _mainCamera->get_target();

        if ( moveCamUp )    target.y += 0.1f;
        if ( moveCamDown )  target.y -= 0.1f;
        if ( moveCamLeft )  target.x -= 0.1f;
        if ( moveCamRight ) target.x += 0.1f;

        _mainCamera->set_target( target );
    }
}

void TestGameState::on_frame_start() {
    // RENDER
    auto renderengine = get_renderengine();

    if ( renderengine ) {
        auto window = renderengine->get_window();

        if ( _mainCamera  ) {
            Viewport4i& viewport = _mainCamera->get_viewport();
            viewport.x = 0;
            viewport.y = 0;
            viewport.w = window->get_renderwidth();
            viewport.h = window->get_renderheight();
        }

        if ( _uiCamera  ) {
            Viewport4i& viewport = _uiCamera->get_viewport();
            viewport.x = 0;
            viewport.y = 0;
            viewport.w = window->get_renderwidth();
            viewport.h = window->get_renderheight();
        }
        

        if ( window->close_requested() ) {
            set_status( GameStateStatus::FINISHED );
        }
    }
}

void TestGameState::on_end()
{

}

weak<Entity> TestGameState::spawn_player( weak<Scene> scene )
{
    auto rendering  = get_renderengine();
    auto input      = get_inputengine();
    auto logic      = get_logicengine();

    weak<Entity> player = nullptr;

    // LOGIC
    if ( logic ) {
        player = logic->add_entity( make_owner<Entity>() );

        auto ctrl = make_owner<Controllable>();
        ctrl->moveSpeed = 0.5f;
        player->add_component( std::move( ctrl ) );

        // INPUT
        if ( input ) {
            //input->add_local_controller( 10, make_owner<PlayerController>( player ) );
        }

        if ( scene ) {
            auto renderer = scene->add_renderer<SpriteRenderer>();
            renderer->set_entity( player );
            renderer->set_texture( rendering->get_texture( "res/textures/dev/test_char.png" ) );
        }
    }

    return player;
}

weak<Entity> TestGameState::spawn_ui( weak<Scene> scene )
{
    auto rendering = get_renderengine();
    auto input = get_inputengine();
    auto logic = get_logicengine();

    weak<Entity> ui = nullptr;

    if ( logic ) {
        ui = logic->add_entity( make_owner<Entity>() );

        ui->position.x = -0.95f;
        ui->position.y =  0.95f;

        if ( scene ) {
            SpriteRenderer::Config config { { 1, 0.5f } ,{ -1, 1 } };
            auto renderer = scene->add_renderer<SpriteRenderer>();
            renderer->set_entity( ui );
            renderer->set_texture( rendering->get_texture( "res/textures/healthmana.png" ) );
            renderer->set_size( { 1, 0.5f } );
            renderer->set_anchor( { -1, 1 } );
        } 
    }

    return ui;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
