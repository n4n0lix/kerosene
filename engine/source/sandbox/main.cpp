#include "engine.h"
#include "engineconfiguration.h"

#define ENGINE_DEBUG

#include "testgamestate.h"
#include "_gl.h"
#include "_global.h"

#include <bitset>
#include "owner.h"

using namespace ENGINE_NAMESPACE;

int main(int argc, char *argv[])
{

    #ifdef ENGINE_DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif


    int result = 0;

    {
        EngineConfiguration& config = EngineConfiguration();
        config.tickrate(100)
            .gamestate(make_owner<TestGameState>());

        Engine engine(config);
        result = engine.run();
    }

    return result;
}
