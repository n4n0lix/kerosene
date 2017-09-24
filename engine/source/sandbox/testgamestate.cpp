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

    // RENDER
    if ( renderengine.ptr_is_usable() ) {
        renderengine->get_window()->set_title( "kerosene - Test" );

        weak<GLWindow> window = get_renderengine()->get_window();
        _camera = make_owner<Camera2D>();
        _camera->set_viewport( 0, 0, window->get_renderwidth(), window->get_renderheight() );

        auto renderer = make_owner<TestRenderer>();
        renderer->init( renderengine );

        _scene = make_owner<Scene>();
        _scene->add_renderer( std::move( renderer ) );
        _scene->add_camera( _camera.get_non_owner() );

        renderengine->add_scene( _scene.get_non_owner() );
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
        }
    }
}

void TestGameState::on_frame_start() {
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
