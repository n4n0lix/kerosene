#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"
#include "quaternion4f.h"
#include "creature.h"

#define GLOBAL_VARS public
#define PLAYER_VARS public
#define LOCAL_VARS  public

ENGINE_NAMESPACE_BEGIN



struct Entity
{
    Entity();

GLOBAL_VARS:
    uint32          id;
    Vector3f        position;
    Vector3f        scale;
    Quaternion4f    rotation;

PLAYER_VARS:

LOCAL_VARS:
    Vector3f        lastPosition;
    Vector3f        lastScale;
    Quaternion4f    lastRotation;

    // TODO: Just for testing purpose. Not every entity must have a creature component
    Creature        creature;
};

ENGINE_NAMESPACE_END