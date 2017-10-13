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
    void        add_component( owner<Component> );
    Component&  get_component( ComponentType );

    template<typename T>
    void        add_component();

private:
    map<ComponentType, owner<Component>>   _components;

};

template<typename T>
void Entity::add_component()
{
    add_component( make_owner<Component>() );
}


ENGINE_NAMESPACE_END

