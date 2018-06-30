#include "stdafx.h"
#include "tilemaprenderer.h"

ENGINE_NAMESPACE_BEGIN

const uint32 TilemapRenderer::DATA_CHANGE_TEST_MS = 250;

TilemapRenderer::TilemapRenderer( weak<Tileset> tileset, Entity entity) :
    _tileset( tileset ),
    _material( Material() ),
    _anchor( Vector2f( 0, 0 ) )
{
    set_entity( entity );
}

void TilemapRenderer::on_init( RenderEngine& pRenderEngine )
{
    _material.set_shader( pRenderEngine.get_shader( "builtin_texture" ) );

    on_dirty();

    LOGGER.log( Level::DEBUG ) << "init tilemaprenderer with id: " << _svao.get_vertex_buffer()->gl_id() << std::endl;
}

void TilemapRenderer::on_render( RenderEngine& pRenderEngine, Camera&, Matrix4f& pProjViewMat, float pInterpolation )
{
    auto entity = get_entity();

    handle_tilemap_data_changed();

    Vector3f position;
    Vector3f scale;
    Quaternion4f rotation;

    if ( entity.has<CTransform>() ) {
        CTransform& transform = entity.get<CTransform>();

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

    _material.set_texture_diffuse( _tileset->get_texture() );
    _material.set_wvp( wvp );
    _material.bind();
    _svao.render_all();
}

void TilemapRenderer::on_cleanup( RenderEngine& )
{
}

// TODO: Change this to an listener. Renderer subscribes to Logic, logic writes events in queue.
void TilemapRenderer::handle_tilemap_data_changed()
{
    auto elapsed = _stopwatchUpdate.elapsed();
    if ( elapsed < DATA_CHANGE_TEST_MS )
        return;

    _stopwatchUpdate.start();
    LOGGER.log( Level::DEBUG ) << "react to data change\n";

    auto entity = get_entity();

    if (entity.has<CTilemapLogic>()) {
      auto& logic = entity.get<CTilemapLogic>();
      auto& tiles = logic.tiles;

      bool tilemapUnchanged = true;

      tilemapUnchanged &= (tiles.size() == _tmpTiles.size());
      tilemapUnchanged &= std::equal(_tmpTiles.begin(), _tmpTiles.end(), tiles.begin());

      if (!tilemapUnchanged) {
        _tmpTiles.clear();
        _tmpTiles.insert(_tmpTiles.end(), tiles.begin(), tiles.end());
        on_dirty();
      }
    }
}

void TilemapRenderer::on_dirty()
{
    auto texture = _material.get_texture_diffuse();
    if ( !texture ) return;

    auto entity = get_entity();

    if ( !entity.has<CTilemapLogic>() ) return;
    auto& logic = entity.get<CTilemapLogic>();

    // 1# Create vertices
    std::vector<Vertex_pt> vertices = {};

    for ( uint32 y = 0; y < logic.height; y++ )
        for ( uint32 x = 0; x < logic.width; x++ ) {
            float x0 = 0.5f*x;
            float x1 = 0.5f*(x+1);
            float y0 = 0.5f*y;
            float y1 = 0.5f*(y+1);

            int index = logic.get_tile( x, y );
            Rect4f uvs = _tileset->get_uvs_by_index( index );

            auto v0 = Vertex_pt( Vector3f( x1, y0, 0 ), Vector2f( uvs.max_x(), uvs.max_y() ));
            auto v1 = Vertex_pt( Vector3f( x0, y0, 0 ), Vector2f( uvs.min_x(), uvs.max_y() ));
            auto v2 = Vertex_pt( Vector3f( x1, y1, 0 ), Vector2f( uvs.max_x(), uvs.min_y() ));
            auto v3 = Vertex_pt( Vector3f( x0, y1, 0 ), Vector2f( uvs.min_x(), uvs.min_y() ));

            auto vrts = std::vector<Vertex_pt> {
                v0, v1, v2,
                v1, v2, v3
            };

            vertices.insert( vertices.end(), vrts.begin(), vrts.end() );
            
        }

    _svao.get_vertex_buffer()->clear();
    _svao.get_vertex_buffer()->add_vertices( vertices );

    LOGGER.log( Level::DEBUG ) << "Tilemaprenderer with id: " << _svao.get_vertex_buffer()->gl_id() << "\n";
}

float TilemapRenderer::render_layer_priority() const
{
    if ( get_entity().has<CTransform>() )
        return get_entity().get<CTransform>().position.z;
    else
        return FLT_MAX;
}

Logger TilemapRenderer::LOGGER = Logger( "TilemapRenderer", Level::WARN );
ENGINE_NAMESPACE_END


