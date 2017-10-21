#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "value.h"
#include "vector2f.h"

ENGINE_NAMESPACE_BEGIN

struct Edge : public Value {
    static Vector2f closes_point_to( Edge e, Vector2f p );

    Edge( Vector2f p0, Vector2f p1 );

    Vector2f p0;
    Vector2f p1;
};

ENGINE_NAMESPACE_END
