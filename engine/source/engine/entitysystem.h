#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "entity.h"

//
// COMPONENT
////////////////////////////////////////

ENGINE_NAMESPACE_BEGIN

//
// SYSTEM
////////////////////////////////////////

struct EntitySystem
{
    void update( Entity& transform );

    Entity create_snapshot_full( Entity& );
    //Entity create_snapshot_delta( Entity& prev, Entity& src );
};

ENGINE_NAMESPACE_END