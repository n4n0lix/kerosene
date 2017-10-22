#include "stdafx.h"
#include "testgamestate.h"

using namespace ENGINE_NAMESPACE;

TestGameState::~TestGameState()
{

}

void TestGameState::on_start()
{
    auto rendering = get_renderengine();
    auto logic = get_logicengine();
    auto input = get_inputengine();


    // RENDER
    if ( rendering ) {
        rendering->get_window()->set_title( "kerosene - Test" );

        _mainScene  = rendering->add_scene<Scene>();
        _mainCamera = _mainScene->add_camera<Camera2D>();
        _mainCamera->set_zoom( 4 );

        _uiScene = rendering->add_scene<Scene>();
        _uiCamera = _uiScene->add_camera<Camera2D>();
        _uiCamera->set_zoom( 4 );
        _ui = spawn_ui( _uiScene );
    }

    if ( logic ) {
        _player = Player_Spawner::Spawn( *logic, rendering, input, _mainScene );
    }


    //
    auto ttex = rendering->get_texture( "res/textures/dev/tile.png" );
    auto tile1 = logic->add_entity(make_owner<Entity>());
    auto rCfg = SpriteRenderer::Config( { { 0, 0 }, { 0.5f, 0.5f }, ttex, tile1 } );
    _mainScene->add_renderer<SpriteRenderer>( rCfg );
    
    tile1->position.y = -0.25;
    tile1->position.z = 0.1;
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
        }
    }

    // Main Camera Update
    if ( _mainCamera && _player ) {
        _mainCamera->set_target( _player->position );
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
