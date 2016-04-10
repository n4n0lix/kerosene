// Header
#include "engineconfiguration.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

EngineConfiguration::EngineConfiguration()
{

}

// TICK RATE
EngineConfiguration& EngineConfiguration::tickrate(uint32_t tickRate)
{
    _tickRate = 10 > tickRate ? 10 : tickRate;
    return *this;
}

uint32_t EngineConfiguration::getTickRate() const {
    return _tickRate;
}

// GAMESTATE
EngineConfiguration& EngineConfiguration::gamestate(unique_ptr<GameState> gamestate)
{
    _gamestate = std::move(gamestate);
    return *this;
}

unique_ptr<GameState> EngineConfiguration::claimGameState()
{
    return std::move(_gamestate);
}

// RENDER ENGINE
EngineConfiguration& EngineConfiguration::render(unique_ptr<IRenderEngine> render)
{
    _render = std::move(render);
    return *this;
}

unique_ptr<IRenderEngine> EngineConfiguration::claimRenderEngine()
{
    // 1# No provided ptr, create disabled instance
    if (_render == nullptr) {
        _render = std::make_unique<DisabledRenderEngine>();
    }

    // 2# Give ownership to caller
    return std::move(_render);
}

// INPUT ENGINE
EngineConfiguration& EngineConfiguration::input(unique_ptr<IInputEngine> input)
{
    _input = std::move(input);
    return *this;
}

unique_ptr<IInputEngine> EngineConfiguration::claimInputEngine()
{
    // 1# No provided ptr, create disabled instance
    if (_input == nullptr) {
        _input = std::make_unique<DisabledInputEngine>();
    }

    // 2# Give ownership to caller
    return std::move(_input);
}

// LOGIC ENGINE
EngineConfiguration& EngineConfiguration::logic(unique_ptr<ILogicEngine> logic)
{
    _logic = std::move(logic);
    return *this;
}

unique_ptr<ILogicEngine> EngineConfiguration::claimLogicEngine()
{
    // 1# No provided ptr, create disabled instance
    if (_logic == nullptr) {
        _logic = std::make_unique<DisabledLogicEngine>();
    }

    // 2# Give ownership to caller
    return std::move(_logic);
}

// PHYSICS ENGINE
EngineConfiguration& EngineConfiguration::physics(unique_ptr<IPhysicsEngine> physics)
{
    _physics = std::move(physics);
    return *this;
}

unique_ptr<IPhysicsEngine> EngineConfiguration::claimPhysicsEngine()
{
    // 1# No provided ptr, create disabled instance
    if (_physics == nullptr) {
        _physics = std::make_unique<DisabledPhysicsEngine>();
    }

    // 2# Give ownership to caller
    return std::move(_physics);
}

// NETWORK
EngineConfiguration& EngineConfiguration::network(unique_ptr<INetworkEngine> network)
{
    _network = std::move(network);
    return *this;
}

unique_ptr<INetworkEngine> EngineConfiguration::claimNetworkEngine()
{
    // 1# No provided ptr, create disabled instance
    if (_network == nullptr) {
        return std::make_unique<DisabledNetworkEngine>();
    }

    // 2# Give ownership to caller
    return std::move(_network);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
