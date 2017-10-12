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
Engine::Engine(EngineConfiguration& config)
{
    // Tick rate
    _tickTime = 1000 / config.getTickRate();

    /* Gamestate */
    // Hand over the ownership
    _gameState = std::move( config.claimGameState() );

    // Render
    _render  = make_owner<RenderEngine>();
    _logic   = make_owner<LogicEngine>();
    _input   = make_owner<InputEngine>();
    _physics = make_owner<PhysicsEngine>();
    _network = make_owner<NetworkEngine>();

    // Post-Conditions
    Ensures( _tickTime > 0 );
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

    // Contains the timestamp in ms of the last calculated tick
    uint64 tickPrevious  = get_current_ms();

    // If lag is larger than ticktime its time to calculate a new tick. In case
    // lags keeps growing we are lagging, cpu can't keep up with the load.
    uint64 lag           = 0;          

    // Multiply to values like   pos.x += speed * delta;   to use tickrate
    // independent values in _speed_
    float  delta         = _tickTime * 0.001f;

    // Mainloop
    while (1)
    {
        // Calculate the tick rate
        uint64 tickCurrent  = get_current_ms();
        uint64 tickDuration = tickCurrent - tickPrevious;
        tickPrevious = tickCurrent;
        lag          += tickDuration;

        // 1# Logic
        while ( lag >= _tickTime )
        {
            PerfStats::instance().tick_start();
            _logic->on_tick_start();

            _input->on_update();
            _logic->on_update( delta );

            if ( !update_gamestate() ) return;

            lag -= _tickTime;
            PerfStats::instance().tick_end();
        }

        // 2# Rendering
        PerfStats::instance().frame_start();
        _gameState->on_frame_start();

        // A float number between [0,1] that tells us how far inbetween ticks we are
        // (0: just had tick update, 0.5 halfway between ticks, 1: new tick is immeninet)
        float interpolation = ((float)lag / (float)_tickTime);

        _render->on_render( interpolation );                              

        _gameState->on_frame_end();
        PerfStats::instance().frame_end();
    }
}

bool Engine::update_gamestate()
{
    // Update Gamestate
    if (_gameState != nullptr && _gameState->get_status() == RUNNING) {
        _gameState->on_update();
    }	

    // End Gamestate
	if (_gameState != nullptr && _gameState->get_status() == FINISHED) {
		_gameState->end();
        _render->on_gamestate_end();
        _logic->on_gamestate_end();
		_gameState = _gameState->take_next_gamestate();
	}

    // Start Gamestate
	if (_gameState != nullptr && _gameState->get_status() == READY) {
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
