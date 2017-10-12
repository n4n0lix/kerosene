#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "object.h"
#include "events.h"

#include "matrix4f.h"
#include "logger.h"
#include "viewport4.h"

ENGINE_NAMESPACE_BEGIN

class Camera : public Object
{
public:
    Matrix4f&   proj_view_mat4();
    
    void        set_as_active();
    
    void        set_clear_color( Vector4f color );
    Vector4f    get_clear_color();
    
    void        set_viewport( Viewport4i viewport );
    void        set_viewport( int32, int32, int32, int32 );
    
    Viewport4i  get_viewport();

EMITTER:
    Emitter<Viewport4i>   OnViewportChanged;

private:
    Matrix4f    _projViewMatrix;

    Viewport4i  _viewport;
    bool        _viewportChanged;

    Vector4f    _clearColor;
};

ENGINE_NAMESPACE_END
