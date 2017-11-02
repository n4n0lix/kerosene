#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

ENGINE_NAMESPACE_BEGIN

typedef uint32 entity_id;

// ENTITY
struct Entity
{
    entity_id       id;

    template<typename MIXIN>
    bool has() { return mixin::has<MIXIN>( id ); }

    template<typename MIXIN>
    MIXIN& access() { return mixin::access<MIXIN>( id ); }

    template<typename MIXIN>
    MIXIN& add() { return mixin::add<MIXIN>( id ); }

    template<typename MIXIN>
    MIXIN& remove() { return mixin::remove<MIXIN>( id ); }
};

ENGINE_NAMESPACE_END

