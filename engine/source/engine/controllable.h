#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "transform.h"
#include "vector2f.h"
#include "component.h"

ENGINE_NAMESPACE_BEGIN

COMPONENT(CControllable, 90)
    void update( float delta );

  GLOBAL:
    int32   health = 0;
    int32   stamina = 0;
    string  name = "Unnamed";
    float   moveSpeed = 1;

  PLAYER:

  LOCAL:
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;
END

ENGINE_NAMESPACE_END

