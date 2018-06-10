#include "stdafx.h"
#include "engine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * Public-constructor
 *
 * @param config A configuration for the engine.
 */
Engine::Engine()
{
    _gameState = make_owner<TestGameState>();

    _render  = make_owner<RenderEngine>();
    _logic   = make_owner<LogicEngine>();
    _input   = make_owner<InputEngine>();
    _physics = make_owner<PhysicsEngine>();
    _network = make_owner<NetworkEngine>();

    // Post-Conditions
    Ensures( _gameState != nullptr );
    Ensures( _render != nullptr );
    Ensures( _input != nullptr );
    Ensures( _logic != nullptr );
    Ensures( _physics != nullptr );
    Ensures( _network != nullptr );
}

/**
 * Starts the engine.
 *
 * @return A status-code when finished. [0: no error occured]
 */
int Engine::run() {

    // StartUp
    _input->on_start();
    _render->on_start( _input.get_non_owner() );
    _logic->on_start();
    _physics->on_start();
    _network->on_start();

    // Mainloop
    mainloop();

    // Shutdown
    _network->on_shutdown();
    _physics->on_shutdown();
    _logic->on_shutdown();
    _render->on_shutdown();
    _input->on_shutdown();

    return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Engine::mainloop() {

    uint64 fps = 144;
    uint64 ups = 50;

    uint64 elapsed = 0;
    uint64 lagUpdate = 0;
    uint64 lagFrame = 0;
    uint64 timePerUpdate = 1000 / ups;
    uint64 timePerFrame = 1000 / fps;

    float  delta = timePerUpdate * 0.001f;

    StopWatch timer;

    while (1)
    {
        // 1# Timing
        elapsed = timer.tick();
        lagUpdate += elapsed;
        lagFrame  += elapsed;

        // 2# Logic
        while ( lagUpdate >= timePerUpdate )
        {
            PerfStats::instance().tick_start();
            _logic->on_tick_start();
            _input->on_update();
            _logic->on_update( delta );
            if ( !update_gamestate() ) return;
            PerfStats::instance().tick_end();

            lagUpdate -= timePerUpdate;
        }
        
        // 3# Rendering         
        if ( lagFrame >= timePerFrame ) {
            PerfStats::instance().frame_start();
            _gameState->on_frame_start();
            _render->on_render( ((float)lagUpdate / (float)timePerUpdate) );
            _gameState->on_frame_end();
            PerfStats::instance().frame_end();

            lagFrame -= timePerFrame;
        }
    }
}

bool Engine::update_gamestate()
{
    // Update Gamestate
    if (_gameState != nullptr && _gameState->get_status() == GameStateStatus::RUNNING) {
        _gameState->on_update();
    }	

    // End Gamestate
	if (_gameState != nullptr && _gameState->get_status() == GameStateStatus::FINISHED) {
		_gameState->end();
        _render->on_gamestate_end();
        _logic->on_gamestate_end();
		_gameState = _gameState->take_next_gamestate();
	}

    // Start Gamestate
	if (_gameState != nullptr && _gameState->get_status() == GameStateStatus::READY) {
        _gameState->set_renderengine( _render.get_non_owner() );
        _gameState->set_inputengine( _input.get_non_owner() );
        _gameState->set_logicengine( _logic.get_non_owner() );

		_gameState->start();
	}

    return _gameState != nullptr;
}

uint64 Engine::get_current_ms()
{
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
