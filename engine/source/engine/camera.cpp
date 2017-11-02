#include "stdafx.h"
#include "camera.h"

ENGINE_NAMESPACE_BEGIN

void Camera::set_viewport( Viewport4i viewport )
{
    _viewport.x = viewport.x;
    _viewport.y = viewport.y;
    _viewport.w = viewport.w;
    _viewport.h = viewport.h;
}

Viewport4i& Camera::get_viewport()
{
    return _viewport;
}

Matrix4f& Camera::proj_view_mat4()
{
    return _projViewMat4;
}


ENGINE_NAMESPACE_END
