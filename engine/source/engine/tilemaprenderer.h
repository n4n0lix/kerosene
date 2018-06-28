#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "simplevertexarray.h"
#include "renderer.h"
#include "tileset.h"
#include "tilemaplogic.h"

ENGINE_NAMESPACE_BEGIN

class TilemapRenderer : public Renderer 
{
public:
    struct Config {
        weak<Entity>  entity;
        string        textureName;
        uint32        tilesetTileWidth;
        uint32        tilesetTileHeight;
    };

public:
    TilemapRenderer( Config config );

protected:
    virtual void on_init( RenderEngine& );
    virtual void on_render( RenderEngine&, Camera&, Matrix4f& pProjViewMat, float pInterpolation );
    virtual void on_cleanup( RenderEngine& );

private:
    void         init_or_update_vertices();


    float         _tileWidth;
    float         _tileHeight;
    uint32        _width;
    uint32        _height;
    uint32        _tilesetTileWidth;
    uint32        _tilesetTileHeight;

    Vector2f      _anchor;

    string        _textureName;
    Material      _material;


    SimpleVertexArray<Vertex_pt> _svao;

    static Rect4f get_uvs_by_index( Texture& tex, uint32 tileWidth, uint32 tileHeight, uint32 index );
    static Logger LOGGER;
};

inline bool is_even( uint32 v ) {
    return (v % 2) == 0;
}


ENGINE_NAMESPACE_END
