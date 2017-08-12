#include "camera.h"

ENGINE_NAMESPACE_BEGIN

Camera::Camera()
{
}

void Camera::render( s_ptr<World> world )
{
    glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
    glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Camera::set_eye(Vector3f eye)
{
    _eye = eye;
}

Vector3f Camera::get_eye()
{
    return _eye;
}

void Camera::set_target(Vector3f target)
{
    _target = target;
}

Vector3f Camera::get_target()
{
    return _target;
}

void Camera::set_clear_color(Vector4f color)
{
    _clearColor = color;
}

Vector4f Camera::get_clear_color()
{
    return _clearColor;
}

void Camera::set_viewport(Viewport4i viewport)
{
    _viewport = viewport;
}

void Camera::set_viewport(int32 x, int32 y, int32 w, int32 h)
{
    set_viewport( Viewport4i(x, y, w, h) );
}

Viewport4i Camera::get_viewport()
{
    return _viewport;
}

Matrix4f Camera::view_matrix()
{
    return Matrix4f::lookAtLH(_eye, _target, Vector3f::Y_AXIS);;
}

Logger Camera::LOGGER = Logger("Camera", Level::DEBUG);

ENGINE_NAMESPACE_END