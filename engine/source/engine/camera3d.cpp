#include "stdafx.h"
#include "camera3d.h"

ENGINE_NAMESPACE_BEGIN

Camera3D::Camera3D()
{
    HandleViewportChange = make_owner<Consumer<Viewport4i>>(
        [&]( Viewport4i viewport )
    {
        update_proj_view_mat();
    } );

    OnViewportChanged += HandleViewportChange.get_non_owner();
}

void Camera3D::set_eye(Vector3f eye)
{
    _eye = eye;
    update_proj_view_mat();
}

Vector3f Camera3D::get_eye()
{
    return _eye;
}

void Camera3D::set_target(Vector3f target)
{
    _target = target;
    update_proj_view_mat();
}

Vector3f Camera3D::get_target()
{
    return _target;
}

void Camera3D::update_proj_view_mat()
{
    proj_view_mat4() = Matrix4f::look_at_lh( _eye, _target, Vector3f::Y_AXIS );
}

ENGINE_NAMESPACE_END
