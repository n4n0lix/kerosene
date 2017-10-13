#include "stdafx.h"
#include "camera2d.h"

ENGINE_NAMESPACE_BEGIN

Camera2D::Camera2D() : _zoom(1)
{
    HandleViewportChange = make_owner<Consumer<Viewport4i>>( 
        [&]( Viewport4i viewport ) 
        { 
            float wa = viewport.w * _zoom * 0.001f;
            float ha = viewport.h * _zoom * 0.001f;

            proj_view_mat4() = Matrix4f::ortho2D( -1 * wa, 1 * wa, -1 * ha, 1 * ha );
        });

    OnViewportChanged += HandleViewportChange.get_non_owner();
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
