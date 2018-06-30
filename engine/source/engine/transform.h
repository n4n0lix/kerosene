#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"
#include "quaternion4f.h"
#include "component.h"

ENGINE_NAMESPACE_BEGIN

COMPONENT(CTransform, 0)
  void update(float delta) override;

GLOBAL:
    Vector3f        position = Vector3f(0, 0, 0);
    Vector3f        scale = Vector3f(1, 1, 1);
    Quaternion4f    rotation = Quaternion4f();

PLAYER:

LOCAL:
    Vector3f        lastPosition = Vector3f(0, 0, 0);
    Vector3f        lastScale = Vector3f(1, 1, 1);
    Quaternion4f    lastRotation = Quaternion4f();
END

ENGINE_NAMESPACE_END
