#include "stdafx.h"
#include "tilemaprenderer.h"

ENGINE_NAMESPACE_BEGIN

TilemapRenderer::TilemapRenderer() :
    _material( Material() ),
    _token( nullptr ),
    entity( nullptr ),
    _anchor( Vector2f( 0, 0 ) ),
    _size( Vector2f( 1, 1 ) )
{
    _vao = std::move( VertexArray<Vertex_pt>() );
}

TilemapRenderer::TilemapRenderer( Config config )
{
}

void TilemapRenderer::on_init( RenderEngine & )
{
}

void TilemapRenderer::on_render( RenderEngine &, Camera &, Matrix4f & pProjViewMat, float pInterpolation )
{
}

void TilemapRenderer::on_cleanup( RenderEngine & )
{
}

void TilemapRenderer::init_or_update_vertices()
{
    uint32 width  = 8;
    uint32 height = 8;
    float tileWidth  = 8.0f;
    float tileHeight = 8.0f;

    // 1# Create vertices
    std::vector<Vector3f> vertices;

    for ( uint32 y = 0; y < height+1; y++ ) {
        for ( uint32 x = 0; x < width+1; x++ ) {
            vertices.push_back( Vector3f( x * tileWidth, y * tileHeight, 0 ) );
        }
    }

    // 2# Create indices
    //   0---1    We iterate over the "upper" vertices, if we are on an even vertex we construct 
    //   | / |    the "upper" triangle (here [0,1,0']), if we are on an odd vertex we construct the
    //  0'---1'    "lower" triangle (here [1,1',0'])

    std::vector<uint32> indices;

    for ( uint32 y = 0; y < height + 1; y++ ) {
        uint32 curRowOffset = y*width;

        for ( uint32 x = 0; x < width + 1; x++ ) {
            uint32 i0, i1, i2;

            if ( is_even(x) ) {
                i0 = x + curRowOffset;
                i1 = i0 + 1; // right of i0
                i2 = i0 + y; // below of i0
            }
            else {
                i0 = x + curRowOffset;
                i1 = i0 + y; // below of i0
                i2 = i1 - 1; // left of  i1
            }

            indices.push_back( i0 );
            indices.push_back( i1 );
            indices.push_back( i2 );
        }
    }

    // 3# Populate vertexbuffer
    _vao.clear();

}

ENGINE_NAMESPACE_END


