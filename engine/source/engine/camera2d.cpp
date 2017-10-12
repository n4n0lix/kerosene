#include "stdafx.h"
#include "camera2d.h"

ENGINE_NAMESPACE_BEGIN

Camera2D::Camera2D() : Camera() 
{
    HandleViewportChange = make_owner<Consumer<Viewport4i>>( 
        [&]( Viewport4i viewport ) 
        { 
            float wa = viewport.w * 0.001f;
            float ha = viewport.h * 0.001f;

            proj_view_mat4() = Matrix4f::ortho2D( -1 * wa, 1 * wa, -1 * ha, 1 * ha );
        });

    OnViewportChanged += HandleViewportChange.get_non_owner();
}

ENGINE_NAMESPACE_END
