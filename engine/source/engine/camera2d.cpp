#include "stdafx.h"
#include "camera2d.h"

ENGINE_NAMESPACE_BEGIN

Camera2D::Camera2D() : 
    _target(0,0,1), 
    _zoom(1)
{
}

void Camera2D::activate( float delta )
{
    auto viewport = get_viewport();

    // Projection
    float right = viewport.w * _zoom * 0.001f;
    float top   = viewport.h * _zoom * 0.001f;
    Matrix4f projMatrix = Matrix4f::ortho2D( -right, right, -top, top );

    // View
    auto eye = Vector3f( _target.x, _target.y, -1 );
    Matrix4f viewMatrix = Matrix4f::look_at_lh( eye, _target, Vector3f::Y_AXIS );

    proj_view_mat4() = viewMatrix * projMatrix;

    glViewport( viewport.x, viewport.y, viewport.w, viewport.h );
}

void Camera2D::set_target( Vector3f target )
{
    _target = target;
}

Vector3f Camera2D::get_target()
{
    return _target;
}

void Camera2D::set_zoom( float zoom )
{
    _zoom = zoom;
}

float Camera2D::get_zoom()
{
    return _zoom;
}

ENGINE_NAMESPACE_END
