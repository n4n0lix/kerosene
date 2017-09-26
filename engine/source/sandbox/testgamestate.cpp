// Header
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
    auto renderengine = get_renderengine();
    auto inputengine = get_inputengine();

    // LOGIC
    _gameObject = make_owner<GameObject>();

    // RENDER
    if ( renderengine.ptr_is_usable() ) {
        renderengine->get_window()->set_title( "kerosene - Test" );

        weak<GLWindow> window = get_renderengine()->get_window();

        auto renderer = make_owner<SpriteRenderer>();
        renderer->set_gameobject( _gameObject.get_non_owner() );

        _scene = renderengine->add_scene( make_owner<Scene>() );
        _camera = _scene->add_camera( make_owner<Camera2D>() );
        _scene->add_renderer( std::move( renderer ) );
    }
}

void TestGameState::on_update()
{
    auto inputengine = get_inputengine();

    // INPUT
    if ( inputengine.ptr_is_usable() ) {
        queue<KeyEvent> keys = get_inputengine()->get_keyevents();

        for ( ; !keys.empty(); keys.pop() )
        {
            KeyEvent evt = keys.front();
            if ( evt.key() == Key::ESCAPE ) {
                set_status( GameStateStatus::FINISHED );
            }

            if ( evt.key() == Key::W ) {
                _wDown = evt.action() == GLFW_PRESS || evt.action() == GLFW_REPEAT;
            }

            if ( evt.key() == Key::S ) {
                _sDown = evt.action() == GLFW_PRESS || evt.action() == GLFW_REPEAT;
            }

            if ( evt.key() == Key::A ) {
                _aDown = evt.action() == GLFW_PRESS || evt.action() == GLFW_REPEAT;
            }

            if ( evt.key() == Key::D ) {
                _dDown = evt.action() == GLFW_PRESS || evt.action() == GLFW_REPEAT;
            }
        }
    }

    // LOGIC
    if ( _aDown )
        _gameObject->transform.position.x -= 0.01f;

    if ( _dDown )
        _gameObject->transform.position.x += 0.01f;

    if ( _wDown )
        _gameObject->transform.position.y += 0.01f;

    if ( _sDown )
        _gameObject->transform.position.y -= 0.01f;
}

void TestGameState::on_frame_start() {
    // RENDER
    auto renderengine = get_renderengine();

    if ( renderengine.ptr_is_usable() ) {
        auto window = renderengine->get_window();
        _camera->set_viewport( 0, 0, window->get_renderwidth(), window->get_renderheight() );

        if ( window->close_requested() ) {
            set_status( GameStateStatus::FINISHED );
        }
    }
}

void TestGameState::on_end()
{
    _gameObject.destroy();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
