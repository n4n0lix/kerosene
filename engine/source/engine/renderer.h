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
            explicit Renderer( Entity e );
            virtual ~Renderer() = default;

    void init( RenderEngine& );
    void render( RenderEngine& , Camera& , Matrix4f&, float );
    void cleanup( RenderEngine& );

    bool is_initialized();

    Entity get_entity() const;
    void   set_entity( Entity );

    int32   render_layer() const;
    void    set_render_layer( int32 layer );


    virtual float render_layer_priority() const = 0;

protected:
    virtual void on_init( RenderEngine& ) = 0;
    virtual void on_render( RenderEngine&, Camera&, Matrix4f&, float ) = 0;
    virtual void on_cleanup( RenderEngine& ) = 0;

private:
    bool			_initialized;
    Entity    _entity;

    int       _renderlayer;
};

ENGINE_NAMESPACE_END
