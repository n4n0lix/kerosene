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

        _mainScene = rendering->add_scene();
        _mainCamera = _mainScene->add_camera<Camera2D>();

        _uiScene = rendering->add_scene();
        _uiCamera = _uiScene->add_camera<Camera2D>();
        _uiCamera->set_right( 1.0f );
        _uiCamera->set_top( 1.0f );

        _ui = spawn_ui( _uiScene );
    }

    if (logic) {
      _player = Player_Spawner::Spawn(*logic, rendering, input, _mainScene);

      _tilemap = Tilemap_Spawner::Spawn(*logic, rendering, input, _mainScene);
      _tilemap.get<CTransform>().position.z = -0.1f;
    }
}

void TestGameState::on_update()
{
    auto inputengine = get_inputengine();

    // INPUT
    if ( inputengine ) {
        std::vector<KeyEvent>& keys = get_inputengine()->get_keyevents();

        for ( auto& event : keys) {
            if ( event.is_consumed() ) continue;

            if ( event.key() == Key::Escape ) {
                set_status( GameStateStatus::FINISHED );
                event.consume();
            }
        }
    }
}

void TestGameState::on_frame_start() {
    // RENDER
    auto renderengine = get_renderengine();

    if ( renderengine ) {
        auto window = renderengine->get_window();

        if ( _mainCamera ) {
            int32 renderWidth = window->get_renderwidth();
            int32 renderHeight = window->get_renderheight();

            _mainCamera->set_viewport( { 0, 0, renderWidth, renderHeight } );
            _mainCamera->set_right( renderWidth/256.0f );
            _mainCamera->set_top( renderHeight/256.0f );

            // Main Camera Update
            if ( _player.has<CTransform>() )
                _mainCamera->set_target( _player.get<CTransform>().position );
        }

        if ( _uiCamera ) {
            int32 renderWidth = window->get_renderwidth();
            int32 renderHeight = window->get_renderheight();
            float aspect = renderWidth / (1.0f*renderHeight);

            _uiCamera->set_right( 1.0f*aspect );
            _uiCamera->set_top( 1.0f );
            _uiCamera->set_viewport( { 0, 0, renderWidth, renderHeight } );

            CTransform& trans = _ui.get<CTransform>();
            trans.position.x = -0.95f * aspect;
            trans.position.y =  0.95f;
        }
            

        if ( window->close_requested() ) 
            set_status( GameStateStatus::FINISHED );

        _fpsText->set_text( "FPS:" + PerfStats::instance().get_fps() );
        //cout << _player->access<has_transform>().position << "\n";
    }
}

void TestGameState::on_end()
{

}

Entity TestGameState::spawn_ui( weak<Scene> scene )
{
    auto rendering = get_renderengine();
    auto input = get_inputengine();
    auto logic = get_logicengine();

    Entity ui = Entity::New();
    CTransform& trans = ui.add<CTransform>();

    trans.position.x = -0.95f;
    trans.position.y =  0.95f;
    trans.position.z = -0.1f;

    if ( scene ) {
      auto tex = rendering->get_texture( "res/textures/healthmana.png" );
      auto rCfg = SpriteRenderer::Config( {
          /*  anchor = */{ -1, 1 },
          /*    size = */{ 0.25f, 0.125f },
          /* texture = */ tex,
          /*  entity = */ ui
      } );

      scene->add_renderer<SpriteRenderer>( rCfg );

      auto oTileset = make_owner<Tileset>( "res/textures/dev/simple_font.png", 8, 8 );
      auto wTileset = rendering->add_resource<Tileset>( "test_font", std::move( oTileset ) );

      _fpsText = scene->add_renderer<TextRenderer>( wTileset, ui );
      _fpsText->set_text( "FPS:" );
    } 

    return ui;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
