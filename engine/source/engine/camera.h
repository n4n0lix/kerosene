#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "noncopyable.h"
#include "events.h"

#include "matrix4f.h"
#include "logger.h"
#include "viewport4.h"

ENGINE_NAMESPACE_BEGIN

class Camera : public noncopyable
{
public:
    virtual void        activate(float delta) = 0;
        
            void        set_viewport( Viewport4i viewport );

            Viewport4i& get_viewport();
            Matrix4f&   proj_view_mat4();

private:
    Matrix4f    _projViewMat4;
    Viewport4i  _viewport;

};

ENGINE_NAMESPACE_END
