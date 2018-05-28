#include "stdafx.h"
#include "tilemaprenderer.h"

ENGINE_NAMESPACE_BEGIN

TilemapRenderer::TilemapRenderer( Config config ) : 
    _textureName( config.textureName ),
    _width( config.width ),
    _height( config.height ),
    _tilesetTileWidth( config.tilesetTileWidth ),
    _tilesetTileHeight( config.tilesetTileHeight ),
    _material( Material() ),
    _anchor( Vector2f( 0, 0 ) )
{
    set_entity( config.entity );
}

void TilemapRenderer::on_init( RenderEngine& pRenderEngine )
{
    auto texture = pRenderEngine.get_texture( _textureName );
    _material.set_texture_diffuse( texture );

    auto shader = pRenderEngine.get_shader( "builtin_texture" );
    _material.set_shader( shader );

    init_or_update_vertices();

    LOGGER.log( Level::DEBUG ) << "init Tilemaprenderer with id: " << _svao.get_vertex_buffer()->gl_id() << std::endl;
}

void TilemapRenderer::on_render( RenderEngine&, Camera&, Matrix4f& pProjViewMat, float pInterpolation )
{
    auto entity = get_entity();
    if ( !get_entity() ) return;

    Vector3f position;
    Vector3f scale;
    Quaternion4f rotation;

    if ( entity->has<has_transform>() ) {
        has_transform& transform = mixin::access<has_transform>( *entity );

        // Interpolate transform, as we are between a calculated tick and a future tick
        position = Vector3f::lerp( transform.lastPosition, transform.position, pInterpolation );
        scale = Vector3f::lerp( transform.lastScale, transform.scale, pInterpolation );
        rotation = Quaternion4f::slerp( transform.lastRotation, transform.rotation, pInterpolation );
    }
    else {
        position = Vector3f( 0, 0, 0 );
        scale = Vector3f( 1, 1, 1 );
        rotation = Quaternion4f();
    }

    Matrix4f matPos = Matrix4f::translation( position );
    Matrix4f matScale = Matrix4f::scaling( scale );
    Matrix4f matRot = Quaternion4f::to_rotation_mat4f( rotation );

#ifdef MAT4_ROW_MAJOR
    Matrix4f world = (matScale * matRot) * matPos;
    Matrix4f wvp = pProjViewMat * world;
#else
    Matrix4f world = (matPos * matRot) * matScale;
    Matrix4f wvp = world * pProjViewMat;
#endif

    _material.set_wvp( wvp );
    _material.bind();
    _svao.render_all();
    //_svao.render_by_indexbuffer();
}

void TilemapRenderer::on_cleanup( RenderEngine& )
{
}

Rect4f TilemapRenderer::get_uvs_by_index( Texture& tex, uint32 tileWidth, uint32 tileHeight, uint32 index )
{
    float uvPerX = (1.0f * tex.get_width()) / tileWidth;
    float uvPerY = (1.0f * tex.get_height()) / tileHeight;

    uint32 x = index % tileWidth;
    uint32 y = index / tileHeight;

    return Rect4f( x * uvPerX, y * uvPerY, uvPerX, uvPerY );
}

void TilemapRenderer::init_or_update_vertices()
{
    auto texture = _material.get_texture_diffuse();
    if ( !texture ) return;

    float tileWidth = 12.0f;
    float tileHeight = 12.0f;

    // 1# Create vertices
    std::vector<Vertex_pt> vertices = {};

    for ( uint32 y = 0; y < _height; y++ )
        for ( uint32 x = 0; x < _width; x++ ) {
            float x0 = x*tileWidth;
            float x1 = x0+tileWidth;
            float y0 = y*tileHeight;
            float y1 = y0+tileHeight;

            Rect4f uvs = TilemapRenderer::get_uvs_by_index( *texture, _tilesetTileWidth, _tilesetTileHeight, 0);

            //Vector3f topLeft  = Vector3f( x0, y0, 0 );
            //Vector3f topRight = Vector3f( x1, y0, 0 );
            //Vector3f botLeft  = Vector3f( x0, y1, 0 );
            //Vector3f botRight = Vector3f( x1, y1, 0 );

            //vertices.push_back( Vertex_pt( topLeft, uvs.top_left() ));
            //vertices.push_back( Vertex_pt( topRight, uvs.top_right() ));
            //vertices.push_back( Vertex_pt( botLeft, uvs.bottom_left() ));
            //vertices.push_back( Vertex_pt( botRight, uvs.bottom_right() ));

            //auto v0 = Vertex_pt( topLeft, uvs.top_left() );
            //auto v1 = Vertex_pt( topRight, uvs.top_right() );
            //auto v2 = Vertex_pt( botLeft, uvs.bottom_left() );
            //auto v3 = Vertex_pt( botRight, uvs.bottom_right() );

            auto v0 = Vertex_pt( Vector3f( x1, y0, 0 ), Vector2f( 1, 1 ) );
            auto v1 = Vertex_pt( Vector3f( x0, y0, 0 ), Vector2f( 0, 1 ) );
            auto v2 = Vertex_pt( Vector3f( x1, y1, 0 ), Vector2f( 1, 0 ) );
            auto v3 = Vertex_pt( Vector3f( x0, y1, 0 ), Vector2f( 0, 0 ) );

            auto vrts = std::vector<Vertex_pt> {
                v0, v1, v2,
                v1, v2, v3
            };

            vertices.insert( vertices.end(), vrts.begin(), vrts.end() );
            
        }

    _svao.get_vertex_buffer()->add_vertices( vertices );

    LOGGER.log( Level::DEBUG ) << "Tilemaprenderer with id: " << _svao.get_vertex_buffer()->gl_id() << std::endl;
}

Logger TilemapRenderer::LOGGER = Logger( "TilemapRenderer", Level::DEBUG );
ENGINE_NAMESPACE_END


