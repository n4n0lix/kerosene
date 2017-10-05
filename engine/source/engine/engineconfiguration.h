#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "gamestate.h"

ENGINE_NAMESPACE_BEGIN

/**
 * A engine configuration builder.
 * Contains pointers to subengine instances, for which the configuration takes
 * no ownership.
 */
class EngineConfiguration
{
public:

            explicit EngineConfiguration();
            ~EngineConfiguration() = default;

    EngineConfiguration&        tickrate(uint32 tickRate);
    uint32                      getTickRate() const;

    EngineConfiguration&        gamestate(owner<GameState> gameState);
    owner<GameState>            claimGameState();

private:

    uint32              _tickRate = 100;
    owner<GameState>    _gamestate = nullptr;

};

ENGINE_NAMESPACE_END
