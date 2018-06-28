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
    float right = _right;
    float top = _top;
    Matrix4f projMatrix = Matrix4f::ortho2D( -right, right, -top, top, -10, 10 );

    float minDiff = 0.01f;  // TODO: Make this configurable
    float camSpeed = 0.25f;  // TODO: Make this configurable
    Matrix4f viewMatrix;

    _lastTarget = Vector3f::lerp( _lastTarget, _target, 0.03f );
    viewMatrix = Matrix4f::translation( -_lastTarget );

#ifdef MAT4_ROW_MAJOR
    proj_view_mat4() = projMatrix * viewMatrix;
#else
    proj_view_mat4() = viewMatrix * projMatrix;
#endif

    glViewport( viewport.x, viewport.y, viewport.w, viewport.h );
}

void Camera2D::set_target( Vector3f target )
{
    _target.x = target.x;
    _target.y = target.y;
    _target.z = 0;
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

void Camera2D::set_right( float right )
{
    _right = right;
}

void Camera2D::set_top( float top )
{
    _top = top;
}

ENGINE_NAMESPACE_END
