#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "events.h"
#include "vector2f.h"
#include "vector3f.h"
#include "matrix4f.h"
#include "viewport4.h"
#include "logger.h"
#include "camera.h"

ENGINE_NAMESPACE_BEGIN

class Camera2D : public Camera
{
public:
                Camera2D();
    
    void        activate(float delta) override;

    void        set_target( Vector3f target );
    Vector3f    get_target();

    void        set_zoom( float zoom );
    float       get_zoom();

private:
    float       _zoom;
    Vector3f    _target;
};

ENGINE_NAMESPACE_END
