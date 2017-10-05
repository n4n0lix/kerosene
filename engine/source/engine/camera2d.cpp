#include "camera2d.h"

ENGINE_NAMESPACE_BEGIN

void Camera2D::set_target(Vector3f target)
{
    _projViewMatrixChanged = true;
    _target = target;
}

Vector3f Camera2D::get_target()
{
    return _target;
}

Matrix4f Camera2D::proj_view_matrix()
{
    if ( _projViewMatrixChanged ) {
        _projViewMatrix = Matrix4f::ortho2D( -1, 1, -1, 1 );
        _projViewMatrixChanged = false;
    }
    return _projViewMatrix;
}

Logger Camera2D::LOGGER = Logger("Camera2D", Level::DEBUG);

ENGINE_NAMESPACE_END
