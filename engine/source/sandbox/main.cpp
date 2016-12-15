#include "engine.h"
#include "engineconfiguration.h"

#include "logger.h"

#include "iinputengine.h"
#include "irenderengine.h"
#include "ilogicengine.h"
#include "iphysicsengine.h"
#include "inetworkengine.h"

#include "disabledinputengine.h"
#define ENGINE_DEBUG

#include "defaultrenderengine.h"
#include "disabledlogicengine.h"
#include "disabledphysicsengine.h"
#include "disablednetworkengine.h"
#include "decimal32.h"

#include "testgamestate.h"
#include "_gl.h"

#include <bitset>

using namespace ENGINE_NAMESPACE;



int main(int argc, char *argv[])
{
    EngineConfiguration& config = EngineConfiguration();
    config.tickrate(100)
          .gamestate(std::make_unique<TestGameState>())
          .render(std::make_unique<DefaultRenderEngine>())
          .input(std::make_unique<DisabledInputEngine>())
          .logic(std::make_unique<DisabledLogicEngine>())
          .physics(std::make_unique<DisabledPhysicsEngine>())
          .network(std::make_unique<DisabledNetworkEngine>());

    Engine(config).run();

    glfwTerminate();
    exit(0);
    return 0;
}
