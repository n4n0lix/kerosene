#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"
#include "quaternion4f.h"
#include "mixins.h"

ENGINE_NAMESPACE_BEGIN

struct has_transform : mixin::Mixin
{
    void update();

GLOBAL:
    Vector3f        position = Vector3f( 0, 0, 0 );
    Vector3f        scale    = Vector3f( 1, 1, 1 );
    Quaternion4f    rotation = Quaternion4f();

PLAYER:

LOCAL:
    Vector3f        lastPosition = Vector3f( 0, 0, 0 );
    Vector3f        lastScale    = Vector3f( 1, 1, 1 );
    Quaternion4f    lastRotation = Quaternion4f();
};

typedef has_transform transform;

DEFINE_MIXIN( has_transform );

ENGINE_NAMESPACE_END
