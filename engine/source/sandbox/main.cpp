#include "engine.h"
#include "engineconfiguration.h"

#define ENGINE_DEBUG

#include "testgamestate.h"
#include "_gl.h"

#include <bitset>

using namespace ENGINE_NAMESPACE;



int main(int argc, char *argv[])
{
    EngineConfiguration& config = EngineConfiguration();
    config.tickrate(100)
          .gamestate(std::make_unique<TestGameState>());

    return Engine(config).run();
}
