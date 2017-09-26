#include "camera3d.h"

ENGINE_NAMESPACE_BEGIN

void Camera3D::set_as_active()
{
    // Set viewport
    if ( _viewportChanged ) {
        glViewport( _viewport.x, _viewport.y, _viewport.w, _viewport.h );
        _viewportChanged = false;
    }

    glClearColor( _clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w );
    glClear( GL_COLOR_BUFFER_BIT );
}

void Camera3D::set_eye(Vector3f eye)
{
    _eye = eye;
    _matrixChanged = true;
}

Vector3f Camera3D::get_eye()
{
    return _eye;
}

void Camera3D::set_target(Vector3f target)
{
    _target = target;
    _matrixChanged = true;
}

Vector3f Camera3D::get_target()
{
    return _target;
}

void Camera3D::set_clear_color(Vector4f color)
{
    _clearColor = color;
}

Vector4f Camera3D::get_clear_color()
{
    return _clearColor;
}

void Camera3D::set_viewport(Viewport4i viewport)
{
    _viewport = viewport;
    _viewportChanged = true;
}

void Camera3D::set_viewport(int32 x, int32 y, int32 w, int32 h)
{
    set_viewport( Viewport4i(x, y, w, h) );
}

Viewport4i Camera3D::get_viewport()
{
    return _viewport;
}

Matrix4f Camera3D::proj_view_matrix()
{
    return Matrix4f::look_at_lh(_eye, _target, Vector3f::Y_AXIS);
}

Logger Camera3D::LOGGER = Logger("Camera3D", Level::DEBUG);

ENGINE_NAMESPACE_END
