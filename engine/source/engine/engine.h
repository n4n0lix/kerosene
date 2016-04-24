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
#include "irenderengine.h"
#include "disabledrenderengine.h"
#include "ilogicengine.h"
#include "disabledlogicengine.h"
#include "iinputengine.h"
#include "disabledinputengine.h"
#include "inetworkengine.h"
#include "disablednetworkengine.h"
#include "iphysicsengine.h"
#include "disabledphysicsengine.h"
#include "engineconfiguration.h"
#include "gamestate.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

/**
 * The main engine object.
 */
class DLL_PUBLIC Engine
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

            /**
             * Public-constructor
             *
             * @param config An engine configuration. Takes over the ownership of all
             *               instances provided by the configuration.
             * @param parent The parent QObject
             */
            explicit Engine(EngineConfiguration& config);

    /**
     * Starts the engine.
     *
     * @return A status-code when finished.
     */
    int run();

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*  METHODS */
    void mainloop();
    void updateGameState();
    uint64 getCurrentMS();

    /*  VARIABLES */
    uint64 _tickTime;
    
    shared_ptr<IRenderEngine>  _render;
    shared_ptr<ILogicEngine>   _logic;
    shared_ptr<IInputEngine>   _input;
    shared_ptr<INetworkEngine> _network;
    shared_ptr<IPhysicsEngine> _physics;

    shared_ptr<GameState> _gameState;

};

ENGINE_NAMESPACE_END
#endif // ENGINE_H
