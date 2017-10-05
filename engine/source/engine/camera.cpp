#include "camera.h"

ENGINE_NAMESPACE_BEGIN

void Camera::set_as_active()
{
    if ( _viewportChanged ) {
        glViewport( _viewport.x, _viewport.y, _viewport.w, _viewport.h );
        _viewportChanged = false;
    }

    glClearColor( _clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w );
    glClear( GL_COLOR_BUFFER_BIT );
}

void Camera::set_clear_color( Vector4f color )
{
    _clearColor = color;
}

Vector4f Camera::get_clear_color()
{
    return _clearColor;
}

void Camera::set_viewport( Viewport4i viewport )
{
    _viewport = viewport;
    _viewportChanged = true;
}

void Camera::set_viewport( int32 pX, int32 pY, int32 pWidth, int32 pHeight )
{
    set_viewport( Viewport4i( pX, pY, pWidth, pHeight ) );
}

Viewport4i Camera::get_viewport()
{
    return _viewport;
}


ENGINE_NAMESPACE_END


