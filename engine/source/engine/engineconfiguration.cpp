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
EngineConfiguration& EngineConfiguration::gamestate(owner<GameState> gamestate)
{
    _gamestate = std::move(gamestate);
    return *this;
}

owner<GameState> EngineConfiguration::claimGameState()
{
    return std::move(_gamestate);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
