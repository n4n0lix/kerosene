#include "camera2d.h"

ENGINE_NAMESPACE_BEGIN

void Camera2D::set_as_active()
{
    // Set viewport
    if ( _viewportChanged ) {
        glViewport( _viewport.x, _viewport.y, _viewport.w, _viewport.h );
        _viewportChanged = false;
    }

    glClearColor( _clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w );
    glClear( GL_COLOR_BUFFER_BIT );
}

void Camera2D::set_target(Vector3f target)
{
    _projViewMatrixChanged = true;
    _target = target;
}

Vector3f Camera2D::get_target()
{
    return _target;
}

void Camera2D::set_clear_color(Vector4f color)
{
    _clearColor = color;
}

Vector4f Camera2D::get_clear_color()
{
    return _clearColor;
}

void Camera2D::set_viewport( Viewport4i viewport )
{
    _viewport = viewport;
    _viewportChanged = true;
}

void Camera2D::set_viewport(int32 x, int32 y, int32 w, int32 h)
{
    set_viewport( Viewport4i(x, y, w, h) );
}

Viewport4i Camera2D::get_viewport()
{
    return _viewport;
}

Matrix4f Camera2D::proj_view_matrix()
{
    if ( _projViewMatrixChanged ) {
        _projViewMatrix = Matrix4f::ortho2D( -1.0f, 1.0f, 1.0f, -1.0f );
    }
    return Matrix4f::IDENTITY;// _projViewMatrix;
}

Logger Camera2D::LOGGER = Logger("Camera2D", Level::DEBUG);

ENGINE_NAMESPACE_END
