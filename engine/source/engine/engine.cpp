// Header
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

    // Init mainloop
    bool programEnd = false;
    uint64_t tickCurrent  = get_current_ms();
    uint64_t tickPrevious = get_current_ms();
    uint64_t tickDuration = 0;
    uint64_t lag          = 0;

    // Mainloop
    while ( !programEnd )
    {
        // Calculate the tick rate
        tickCurrent  = get_current_ms();
        tickDuration = tickCurrent - tickPrevious;
        tickPrevious = tickCurrent;
        lag          += tickDuration;

        // 1# Logic
        while ( lag >= _tickTime )
        {
            _input->on_update();

            update_gamestate();

            _logic->on_update();
            _physics->on_update();

            lag -= _tickTime;
        }

        // 2# Rendering
        _render->set_interpolation( (float)((double)lag / (double)_tickTime) ); // Add '+ 1' to switch to extrapolation
        _render->on_render( _gameState->get_gameobjects() );

        programEnd = _render->is_exit_requested();
    }
}

void Engine::update_gamestate()
{
    // Update Gamestate
    if (_gameState != nullptr && _gameState->get_status() == RUNNING) {
        _gameState->update();
    }	

    // End Gamestate
	if (_gameState != nullptr && _gameState->get_status() == FINISHED) {
		_gameState->end();
        _gameState->set_renderengine( nullptr );

		_gameState = _gameState->take_next_gamestate();
	}

    // Start Gamestate
	if (_gameState != nullptr && _gameState->get_status() == READY) {
        _gameState->set_renderengine( _render.get_non_owner() );
        _gameState->set_inputengine( _input.get_non_owner() );

		_gameState->start();
	}
}

uint64_t Engine::get_current_ms()
{
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
