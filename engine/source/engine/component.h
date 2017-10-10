#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

ENGINE_NAMESPACE_BEGIN

#define GLOBAL_VARS public
#define PLAYER_VARS public
#define LOCAL_VARS public

enum ComponentType : uint32 {
    ctype_Unkown,
    ctype_Entity, 
    ctype_Controllable
};

struct Component {
    Component( ComponentType type );
    virtual ~Component() = default;

    ComponentType type;
};

ENGINE_NAMESPACE_END
