#ifndef ENGINECONFIGURATION_H
#define ENGINECONFIGURATION_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "gamestate.h"
#include "irenderengine.h"
#include "disabledrenderengine.h"
#include "iinputengine.h"
#include "disabledinputengine.h"
#include "ilogicengine.h"
#include "disabledlogicengine.h"
#include "iphysicsengine.h"
#include "disabledphysicsengine.h"
#include "inetworkengine.h"
#include "disablednetworkengine.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

/**
 * A engine configuration builder.
 * Contains pointers to subengine instances, for which the configuration takes
 * no ownership.
 */
class DLL_PUBLIC EngineConfiguration
{

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit EngineConfiguration();

    EngineConfiguration&            tickrate(uint32_t tickRate);
    uint32_t                        getTickRate() const;

    EngineConfiguration&            gamestate(unique_ptr<GameState> gameState);
    unique_ptr<GameState>           claimGameState();

    EngineConfiguration&            render(unique_ptr<IRenderEngine> render);
    unique_ptr<IRenderEngine>       claimRenderEngine();

    EngineConfiguration&            input(unique_ptr<IInputEngine> input);
    unique_ptr<IInputEngine>        claimInputEngine();

    EngineConfiguration&            logic(unique_ptr<ILogicEngine> logic);
    unique_ptr<ILogicEngine>        claimLogicEngine();

    EngineConfiguration&            physics(unique_ptr<IPhysicsEngine> physics);
    unique_ptr<IPhysicsEngine>      claimPhysicsEngine();

    EngineConfiguration&            network(unique_ptr<INetworkEngine> network);
    unique_ptr<INetworkEngine>      claimNetworkEngine();

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    uint32_t _tickRate = 100;

    unique_ptr<GameState>  _gamestate = nullptr;

    unique_ptr<IRenderEngine>  _render  = nullptr;
    unique_ptr<IInputEngine>   _input   = nullptr;
    unique_ptr<ILogicEngine>   _logic   = nullptr;
    unique_ptr<IPhysicsEngine> _physics = nullptr;
    unique_ptr<INetworkEngine> _network = nullptr;
};

ENGINE_NAMESPACE_END
#endif // ENGINECONFIGURATION_H
