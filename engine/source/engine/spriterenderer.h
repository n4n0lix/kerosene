#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "mixins.h"
#include "transform.h"
#include "renderer.h"
#include "matrix4f.h"
#include "shader.h"
#include "material.h"
#include "texture.h"
#include "simplevertexarray.h"
#include "attribvertexarray.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class SpriteRenderer : public Renderer
{
public:
    struct Config {
        Vector2f anchor;
        Vector2f size;
        weak<Texture> texture;
        weak<Entity>  entity;
    };

public:
    SpriteRenderer();
    SpriteRenderer( Config config );

    void    set_texture( weak<Texture> );
    void    set_anchor( Vector2f anchor );
    void    set_size( Vector2f size );

protected:
    virtual void on_init( RenderEngine& );
    virtual void on_render( RenderEngine&, Camera&, Matrix4f& pProjViewMat, float pInterpolation );
    virtual void on_cleanup( RenderEngine& );

private:
    void                init_or_update_vertices();

    bool                        _verticesHaveChanged;
    Vector2f                    _size;
    Vector2f                    _anchor;
    Material                    _material;

    SimpleVertexArray<Vertex_pt> _svao;
    AttribVertexArray<Vertex_pt> _avao;

    static Logger LOGGER;
};

ENGINE_NAMESPACE_END
