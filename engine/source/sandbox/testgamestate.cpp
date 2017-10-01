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
    auto logicengine = get_logicengine();

    // LOGIC
    _entity = logicengine->add_entity( make_owner<Entity>() );

    // RENDER
    if ( renderengine.ptr_is_usable() ) {
        renderengine->get_window()->set_title( "kerosene - Test" );

        weak<GLWindow> window = get_renderengine()->get_window();

        auto renderer = make_owner<SpriteRenderer>();
        renderer->set_entity( _entity );

        _scene = renderengine->add_scene( make_owner<Scene>() );
        _camera = _scene->add_camera( make_owner<Camera2D>() );
        _renderer = _scene->add_renderer( std::move( renderer ) );
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

            if ( evt.key() == Key::E ) {
                _renderer->extrapolation = !_renderer->extrapolation;
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
        _entity->transform.position.x -= 0.01f;

    if ( _dDown )
        _entity->transform.position.x += 0.01f;

    if ( _wDown )
        _entity->transform.position.y += 0.01f;

    if ( _sDown )
        _entity->transform.position.y -= 0.01f;
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

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
