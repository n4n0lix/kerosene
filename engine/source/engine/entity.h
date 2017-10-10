#pragma once

// Std-Includes
#include <bitset>

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"
#include "quaternion4f.h"
#include "component.h"
#include "nullable.h"

ENGINE_NAMESPACE_BEGIN

// ENTITY
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


public:
    bool        has_component( ComponentType );
    void        add_component( unique<Component> );
    Component&  get_component( ComponentType );

private:
    map<ComponentType, unique<Component>>   _components;

};

ENGINE_NAMESPACE_END