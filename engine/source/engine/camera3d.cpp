#include "camera3d.h"

ENGINE_NAMESPACE_BEGIN

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

Matrix4f Camera3D::proj_view_matrix()
{
    return Matrix4f::look_at_lh(_eye, _target, Vector3f::Y_AXIS);
}

Logger Camera3D::LOGGER = Logger("Camera3D", Level::DEBUG);

ENGINE_NAMESPACE_END
