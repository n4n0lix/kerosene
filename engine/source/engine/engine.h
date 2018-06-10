#pragma once

// Std-Includes
#include <assert.h>
#include <chrono>
#include <thread>

// Other Includes

// Internal Includes
#include "_global.h"
#include "renderengine.h"
#include "logicengine.h"
#include "inputengine.h"
#include "networkengine.h"
#include "physicsengine.h"
#include "testgamestate.h"
#include "gamestate.h"
#include "perfstats.h"
#include "stopwatch.h"

ENGINE_NAMESPACE_BEGIN

/**
 * The main engine object.
 */
class Engine
{
public:

    const string  ENGINE_NAME       = "KerosineEngine";
    const string  ENGINE_VERSION    = "v0.0.1-indev";


            Engine();
            ~Engine() = default;

    int run();

private:

    /*  METHODS */
    void mainloop();
    bool update_gamestate();
    uint64 get_current_ms();

    /*  VARIABLES */   
    owner<RenderEngine>  _render;
    owner<LogicEngine>   _logic;
    owner<InputEngine>   _input;
    owner<NetworkEngine> _network;
    owner<PhysicsEngine> _physics;

    owner<GameState>     _gameState;

};

ENGINE_NAMESPACE_END
