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

typedef uint32 entity_id;

// ENTITY
struct Entity
{
    Entity();

GLOBAL_VARS:
    entity_id       id;
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
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

    add_component( make_owner<T>() );
}


ENGINE_NAMESPACE_END

