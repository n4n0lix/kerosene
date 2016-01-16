// Header
#include "engine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Engine::Engine(EngineConfiguration& config)
{
    // Tick rate
    _tickTime = 1000 / config.getTickRate();

    /* Gamestate */
    // Hand over the ownership
    _gameState = shared_ptr<GameState>{ config.claimGameState().release() }; // Hand over the ownership

    // Render
    _render =   shared_ptr<IRenderEngine>{ config.claimRenderEngine().release() }; // Hand over the ownership

    // Logic
    _logic =    shared_ptr<ILogicEngine>{ config.claimLogicEngine().release() }; // Hand over the ownership

    // Input
    _input =    shared_ptr<IInputEngine>{ config.claimInputEngine().release() }; // Hand over the ownership

    // Physics
    _physics =  shared_ptr<IPhysicsEngine>{ config.claimPhysicsEngine().release() }; // Hand over the ownership

    // Network
    _network =  shared_ptr<INetworkEngine>{ config.claimNetworkEngine().release() }; // Hand over the ownership

    // Post-Conditions
    assert(_tickTime > 0);
    assert(_gameState != nullptr);
    assert(_render != nullptr);
    assert(_input != nullptr);
    assert(_logic != nullptr);
    assert(_physics != nullptr);
    assert(_network != nullptr);
}

int Engine::run() {

    // StartUp
    _render->onStart();
    _input->onStart();
    _logic->onStart();
    _physics->onStart();
    _network->onStart();

    // Mainloop
    mainloop();

    // Shutdown
    _network->onShutdown();
    _physics->onShutdown();
    _logic->onShutdown();
    _input->onShutdown();
    _render->onShutdown();

    return 0;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Engine::mainloop() {

    // Init mainloop
    bool programEnd = false;
    uint64_t tickCurrent  = getCurrentMS();
    uint64_t tickPrevious = getCurrentMS();
    uint64_t tickDuration = 0;
    uint64_t lag          = 0;

    // Mainloop
    while ( !programEnd )
    {
        // Calculate the tick rate
        tickCurrent  = getCurrentMS();
        tickDuration = tickCurrent - tickPrevious;
        tickPrevious = tickCurrent;
        lag          += tickDuration;

        // 1# Logic
        while ( lag >= _tickTime )
        {
            _input->onUpdate();

            updateGameState();

            _logic->onUpdate();
            _physics->onUpdate();

            lag -= _tickTime;
        }

        // 2# Rendering
        _render->setInterpolation((float)((double) lag / (double) _tickTime)); // Add '+ 1' to switch to extrapolation

        _render->onUpdate();

        programEnd = _render->isExitRequested();
    }
}

void Engine::updateGameState()
{
    if (_gameState != nullptr) {
        _gameState->update();

        if (_gameState->getStatus() == FINISHED) {
            _gameState->end();
            _gameState = _gameState->getNext();

            if (_gameState != nullptr) {
                _gameState->start();
            }
        }
    }
}

uint64_t Engine::getCurrentMS()
{
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
