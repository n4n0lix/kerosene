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
}

ENGINE_NAMESPACE_END


