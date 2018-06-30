#include "stdafx.h"
#include "transform.h"

ENGINE_NAMESPACE_BEGIN

void CTransform::update(float delta) {
    lastPosition = position;
    lastScale    = scale;
    lastRotation = rotation;
}

ENGINE_NAMESPACE_END
