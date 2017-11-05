#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "vertexarray.h"
#include "renderer.h"

ENGINE_NAMESPACE_BEGIN

class TilemapRenderer : public Renderer 
{
public:
    struct Config {
        weak<Texture> texture;
        weak<Entity>  entity;
        Vector2f      tileSize;
        uint32        width;
        uint32        height;
    };

public:
    TilemapRenderer();
    TilemapRenderer( Config config );

    void    set_texture( weak<Texture> );
    void    set_anchor( Vector2f anchor );
    void    set_size( Vector2f size );

protected:
    virtual void on_init( RenderEngine& );
    virtual void on_render( RenderEngine&, Camera&, Matrix4f& pProjViewMat, float pInterpolation );
    virtual void on_cleanup( RenderEngine& );

private:
    void                init_or_update_vertices();
    Vector2f                    _size;
    Vector2f                    _anchor;
    Material                    _material;
    VertexArray<Vertex_pt>      _vao;

    owner<VertexToken>          _token;
    weak<Entity>                entity;

    static Logger LOGGER;
};

inline bool is_even( uint32 v ) {
    return (v % 2) == 0;
}


ENGINE_NAMESPACE_END
