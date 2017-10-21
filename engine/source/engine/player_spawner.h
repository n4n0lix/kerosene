#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

#include "logicengine.h"
#include "renderengine.h"
#include "inputengine.h"

#include "scene.h"
#include "spriterenderer.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using namespace ENGINE_NAMESPACE;

class Player_Spawner {
    static weak<Entity> Spawn( LogicEngine& logic, weak<RenderEngine> render, weak<InputEngine> input, weak<Scene> mainScene );
};