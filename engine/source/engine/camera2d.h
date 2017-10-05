#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
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
                        Camera2D() : Camera() {}
    virtual             ~Camera2D() = default;


    virtual Matrix4f    proj_view_matrix();

            void        set_target( Vector3f target );
            Vector3f    get_target();


            bool        _projViewMatrixChanged;
            Matrix4f    _projViewMatrix;

            Vector3f    _target;


private:
    static  Logger      LOGGER;
};

ENGINE_NAMESPACE_END
