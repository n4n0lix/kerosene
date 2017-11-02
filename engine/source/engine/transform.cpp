#include "stdafx.h"
#include "transform.h"

ENGINE_NAMESPACE_BEGIN

REGISTER_MIXIN( 0, has_transform )

void has_transform::update() {
    lastPosition = position;
    lastScale    = scale;
    lastRotation = rotation;
}

ENGINE_NAMESPACE_END
