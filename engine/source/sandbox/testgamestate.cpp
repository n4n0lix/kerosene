#include "stdafx.h"
#include "testgamestate.h"

using namespace ENGINE_NAMESPACE;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Protected                       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TestGameState::~TestGameState()
{

}

void TestGameState::on_start()
{
    auto rendering = get_renderengine();

    // RENDER
    if ( rendering.is_ptr_usable() ) {
        rendering->get_window()->set_title( "kerosene - Test" );

        _mainScene  = rendering->add_scene<Scene>();
        _mainCamera = _mainScene->add_camera<Camera2D>();
    }

    _player = spawn_player( _mainScene );
}

void TestGameState::on_update()
{
    auto inputengine = get_inputengine();

    // INPUT
    if ( inputengine.is_ptr_usable() ) {
        vector<KeyEvent>& keys = get_inputengine()->get_keyevents();

        for ( auto& event : keys) {
            if ( event.is_consumed() ) continue;

            if ( event.key() == Key::ESCAPE ) {
                set_status( GameStateStatus::FINISHED );
                event.consume();
            }
        }
    }
}

void TestGameState::on_frame_start() {
    // RENDER
    auto renderengine = get_renderengine();

    if ( renderengine.is_ptr_usable() ) {
        auto window = renderengine->get_window();

        if ( _mainCamera != nullptr ) {
            _mainCamera->set_viewport( 0, 0, window->get_renderwidth(), window->get_renderheight() );
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

    weak<Entity> entity = nullptr;

    // LOGIC
    if ( logic.is_ptr_usable() ) {
        entity = logic->add_entity( make_owner<Entity>() );
        entity->add_component( make_owner<Controllable>() );

        // INPUT
        if ( input.is_ptr_usable() ) {
            input->add_local_controller( 10, make_owner<PlayerController>( entity ) );
        }

        if ( scene.is_ptr_usable() ) {
            scene->add_renderer( make_owner<SpriteRenderer>( entity ) );
        }
    }

    return entity;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
