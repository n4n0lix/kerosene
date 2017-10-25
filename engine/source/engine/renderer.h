#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "renderengine.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class RenderEngine;

//
// - Handles ownership of rendering resources

class Renderer : public noncopyable
{
public:
            Renderer();

    void init( RenderEngine& );
    void render( RenderEngine& , Camera& , Matrix4f&, float );
    void cleanup( RenderEngine& );

    bool is_initialized();

protected:
    virtual void on_init( RenderEngine& ) = 0;
    virtual void on_render( RenderEngine&, Camera&, Matrix4f&, float ) = 0;
    virtual void on_cleanup( RenderEngine& ) = 0;

private:
    bool			    _initialized;

};

ENGINE_NAMESPACE_END
