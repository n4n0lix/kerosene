#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "matrix4f.h"
#include "logger.h"
#include "viewport4.h"

ENGINE_NAMESPACE_BEGIN

class Camera
{
public:
                        Camera() : _viewport(Viewport4i()), _viewportChanged(true), _clearColor(Vector4f()) {};
    virtual             ~Camera() = default;


    virtual Matrix4f    proj_view_matrix() = 0;


            void        set_as_active();
            void        set_clear_color( Vector4f color );
            Vector4f    get_clear_color();
            void        set_viewport( Viewport4i viewport );
            void        set_viewport( int32, int32, int32, int32 );

            Viewport4i  get_viewport();


private:
            Viewport4i  _viewport;
            bool        _viewportChanged;
            Vector4f    _clearColor;
};

ENGINE_NAMESPACE_END
