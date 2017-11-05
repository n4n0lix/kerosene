#include "stdafx.h"
#include "spriterenderer.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SpriteRenderer::SpriteRenderer() : 
    _material( Material() ), _token( nullptr ),
    _anchor( Vector2f(0,0) ), _size( Vector2f(1,1) )
{

}

SpriteRenderer::SpriteRenderer( Config config ) : SpriteRenderer()
{
    set_entity( config.entity );
    set_texture( config.texture );
    set_anchor( config.anchor );
    set_size( config.size );
}

void SpriteRenderer::set_texture( weak<Texture> texture )
{
    _material.set_texture_diffuse( texture );
}

void SpriteRenderer::set_anchor( Vector2f anchor )
{
    _anchor = anchor;
    init_or_update_vertices();
}

void SpriteRenderer::set_size( Vector2f size )
{
    _size = size;
    init_or_update_vertices();
}

void SpriteRenderer::on_init( RenderEngine& pRenderEngine )
{   
    _material.set_shader( pRenderEngine.get_shader( "builtin_texture" ) );
    init_or_update_vertices();
}

void SpriteRenderer::on_render( RenderEngine& pRenderEngine, Camera& pCamera, Matrix4f& pProjViewMat, float pInterpolation )
{
    auto entity = get_entity();
    if ( !entity ) return; // TODO: Try to remove this

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
    Matrix4f world  = (matScale * matRot) * matPos;
    Matrix4f wvp    = pProjViewMat * world;
#else
    Matrix4f world = (matPos * matRot) * matScale;
    Matrix4f wvp    = world * pProjViewMat;
#endif

    _material.set_wvp( wvp );
    _material.bind();
    _svao.render_all();
}

void SpriteRenderer::on_cleanup( RenderEngine& pRenderEngine )
{
    _vao.clear();
    _token.destroy();
}

void SpriteRenderer::init_or_update_vertices()
{
    // Calcualte hellper variables for setting up the anchoring like
    //              [-1, 1] [0, 1] [1, 1]
    //              [-1, 0] [0, 0] [1, 0]
    //              [-1,-1] [0,-1] [1,-1]

    float w = _size.x / 2;
    float h = _size.y / 2;

    float x = _anchor.x * w;
    float y = _anchor.y * h;

    std::vector<Vertex_pt> vertices = std::vector<Vertex_pt>();

    vertices.push_back( Vertex_pt( {  w - x, -h - y, 0 }, { 1, 1 } ) );
    vertices.push_back( Vertex_pt( { -w - x, -h - y, 0 }, { 0, 1 } ) );
    vertices.push_back( Vertex_pt( {  w - x,  h - y, 0 }, { 1, 0 } ) );
    vertices.push_back( Vertex_pt( { -w - x, -h - y, 0 }, { 0, 1 } ) );
    vertices.push_back( Vertex_pt( {  w - x,  h - y, 0 }, { 1, 0 } ) );
    vertices.push_back( Vertex_pt( { -w - x,  h - y, 0 }, { 0, 0 } ) );

    _svao.get_vertex_buffer()->add_vertices( vertices );
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
