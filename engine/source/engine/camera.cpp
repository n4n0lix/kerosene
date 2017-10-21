#include "stdafx.h"
#include "camera.h"

ENGINE_NAMESPACE_BEGIN

Viewport4i& Camera::get_viewport()
{
    return _viewport;
}

Matrix4f& Camera::proj_view_mat4()
{
    return _projViewMat4;
}


ENGINE_NAMESPACE_END
