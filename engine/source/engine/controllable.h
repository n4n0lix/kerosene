#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "mixins.h"
#include "transform.h"
#include "vector2f.h"

ENGINE_NAMESPACE_BEGIN

struct Controllable : mixin::Mixin
{
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
};


DEFINE_MIXIN( Controllable );

ENGINE_NAMESPACE_END

