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

        _uiScene = rendering->add_scene<Scene>();
        _uiCamera = _uiScene->add_camera<Camera2D>();
        _uiCamera->set_right( 1.0f );
        _uiCamera->set_top( 1.0f );

        _ui = spawn_ui( _uiScene );
    }

    if ( logic ) {
        _player = Player_Spawner::Spawn( *logic, rendering, input, _mainScene );
    }


    if ( _mainScene ) {
        auto ttex = rendering->get_texture( "res/textures/dev/tile.png" );
        auto tile1 = logic->add_entity( make_owner<Entity>() );
        tile1->add<has_transform>();

        auto rCfg = SpriteRenderer::Config( {
            /*  anchor = */{ 0, 0 },
            /*    size = */{ (float)ttex->get_width(), (float)ttex->get_height() },
            /* texture = */ ttex,
            /*  entity = */ tile1
        } );

        _mainScene->add_renderer<SpriteRenderer>( rCfg );

        has_transform& trans = mixin::access<has_transform>( *tile1 );
        trans.position.y = 0;
        trans.position.z = -0.1f;
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
            _mainCamera->set_right( renderWidth/8.0f );
            _mainCamera->set_top( renderHeight/8.0f );

            // Main Camera Update
            if ( _player && _player->has<has_transform>() )
                _mainCamera->set_target( _player->access<has_transform>().position );
        }

        if ( _uiCamera ) {
            int32 renderWidth = window->get_renderwidth();
            int32 renderHeight = window->get_renderheight();
            float aspect = renderWidth / (1.0f*renderHeight);

            _uiCamera->set_right( 1.0f*aspect );
            _uiCamera->set_top( 1.0f );
            _uiCamera->set_viewport( { 0, 0, renderWidth, renderHeight } );

            has_transform& trans = _ui->access<transform>();
            trans.position.x = -0.95f * aspect;
            trans.position.y =  0.95f;
        }
            

        if ( window->close_requested() ) 
            set_status( GameStateStatus::FINISHED );

        //cout << _player->access<has_transform>().position << "\n";
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
        has_transform& trans = ui->add<transform>();

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
        } 
    }

    return ui;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
