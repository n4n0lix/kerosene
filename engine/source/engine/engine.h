#ifndef ENGINE_H
#define ENGINE_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <assert.h>
#include <chrono>

// Other Includes

// Internal Includes
#include "_global.h"
#include "renderengine.h"
#include "logicengine.h"
#include "inputengine.h"
#include "networkengine.h"
#include "physicsengine.h"
#include "engineconfiguration.h"
#include "gamestate.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

/**
 * The main engine object.
 */
class Engine
{

public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    const string  ENGINE_NAME       = "KerosineEngine";
    const string  ENGINE_VERSION    = "v0.0.1-indev";

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            explicit Engine(EngineConfiguration& config);
            ~Engine() = default;

    int run();

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*  METHODS */
    void mainloop();
    void update_gamestate();
    uint64 get_current_ms();

    /*  VARIABLES */
    uint64 _tickTime;
    
    owner<RenderEngine>  _render;
    owner<LogicEngine>   _logic;
    owner<InputEngine>   _input;
    owner<NetworkEngine> _network;
    owner<PhysicsEngine> _physics;

    owner<GameState>     _gameState;

};

ENGINE_NAMESPACE_END
#endif // ENGINE_H
