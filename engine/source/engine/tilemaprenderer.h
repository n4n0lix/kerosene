#pragma once

// Std-Includes
#include <algorithm>

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
    static const uint32 DATA_CHANGE_TEST_MS;

    TilemapRenderer( weak<Tileset> tileset, Entity entity=Entity::None );
    ~TilemapRenderer() = default;

    // Inhereted by Renderer
    virtual float render_layer_priority() const override;
protected:

    // Inhereted by Renderer
    virtual void on_init( RenderEngine& ) override;
    virtual void on_render( RenderEngine&, Camera&, Matrix4f& pProjViewMat, float pInterpolation ) override;
    virtual void on_cleanup( RenderEngine& ) override;

private:
    void         on_dirty();
    void         handle_tilemap_data_changed();


    float         _tileWidth;
    float         _tileHeight;
    uint32        _width;
    uint32        _height;

    Vector2f       _anchor;
    weak<Tileset>  _tileset;
    Material       _material;

    StopWatch           _stopwatchUpdate;
    std::vector<int>    _tmpTiles;

    SimpleVertexArray<Vertex_pt> _svao;

    static Logger LOGGER;
};

inline bool is_even( uint32 v ) {
    return (v % 2) == 0;
}


ENGINE_NAMESPACE_END
