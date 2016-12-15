#include "camera.h"

ENGINE_NAMESPACE_BEGIN

Camera::Camera()
{
}

void Camera::render()
{

}

Matrix4f Camera::view_matrix()
{
    return Matrix4f::lookAtLH(_eye, _target, Vector3f::Y_AXIS);;
}

Logger Camera::LOGGER = Logger("Camera", Level::DEBUG);

ENGINE_NAMESPACE_END
