#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "vector3f.h"
#include "matrix4f.h"
#include "viewport4.h"
#include "logger.h"
#include "camera.h"


ENGINE_NAMESPACE_BEGIN

class Camera3D : public Camera
{
public:
              Camera3D() : Camera() {}
    virtual   ~Camera3D() = default;


    virtual Matrix4f    proj_view_matrix();

            void        set_eye( Vector3f eye );
            Vector3f    get_eye();

            void        set_target( Vector3f target );
            Vector3f    get_target();


            bool        _matrixChanged;
            Matrix4f    _viewMatrix;

            Vector3f    _eye;
            Vector3f    _target;


private:
    static  Logger      LOGGER;
};

ENGINE_NAMESPACE_END
