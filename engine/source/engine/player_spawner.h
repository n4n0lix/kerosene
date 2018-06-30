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
#include "tileset.h"
#include "textrenderer.h"
#include "tilemaprenderer.h"

#include "tilemaplogic.h"
#include "playercontroller.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using namespace ENGINE_NAMESPACE;

struct Player_Spawner {
    static Entity Spawn( LogicEngine& logic, weak<RenderEngine> render, weak<InputEngine> input, weak<Scene> mainScene );

    static void SetupSubsprites( SpriteRenderer& );
    static void SetupAnim0Idle( SpriteRenderer& );
    static void SetupAnim1LeftWalk( SpriteRenderer& );
    static void SetupAnim2RightWalk( SpriteRenderer& );
};