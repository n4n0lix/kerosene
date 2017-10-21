#include "stdafx.h"
#include "spriterenderer.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SpriteRenderer::SpriteRenderer()
    : 
    _material(Material()), 
    //_vao(VertexArray<Vertex_pt>()), 
    _token(nullptr), 
    _entity(nullptr),
    _anchor(Vector2f(0,0)),
    _size(Vector2f(1,1))
{
    _vao = std::move( VertexArray<Vertex_pt>() );
}

SpriteRenderer::SpriteRenderer( Config config ) : SpriteRenderer()
{
    set_entity( config.entity );
    set_texture( config.texture );
    set_anchor( config.anchor );
}

void SpriteRenderer::set_entity( weak<Entity> pEntity )
{
    _entity = pEntity;
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
    // Interpolate transform, as we are between a calculated tick and a future tick
    Vector3f        position = Vector3f::lerp( _entity->lastPosition, _entity->position, pInterpolation );
    Vector3f        scale    = Vector3f::lerp( _entity->lastScale, _entity->scale, pInterpolation );
    Quaternion4f    rotation = Quaternion4f::slerp( _entity->lastRotation, _entity->rotation, pInterpolation );

    Matrix4f        matPos   = Matrix4f::translation( position );
    Matrix4f        matScale = Matrix4f::scaling( scale );
    Matrix4f        matRot   = Quaternion4f::to_rotation_mat4f( rotation );

    Matrix4f        world = (matScale * matRot) * matPos;

    // Set the world x view x projection matrix
    Matrix4f wvp = pProjViewMat * world;

    _material.set_wvp( wvp );
    _material.bind();
    _vao.render();
}

void SpriteRenderer::on_cleanup( RenderEngine& pRenderEngine )
{
    _vao.clear();
    _token.destroy();
}

void SpriteRenderer::init_or_update_vertices()
{
    if ( _token != nullptr ) {
        _vao.remove_render_static( _token.get_non_owner() );
        _vao.remove_vertices( std::move( _token ) );
    }

    // Calcualte hellper variables for setting up the anchoring like
    //              [-1, 1] [0, 1] [1, 1]
    //              [-1, 0] [0, 0] [1, 0]
    //              [-1,-1] [0,-1] [1,-1]

    float w = _size.x / 2;
    float h = _size.y / 2;

    float x = _anchor.x * w;
    float y = _anchor.y * h;

    vector<Vertex_pt> vertices = vector<Vertex_pt>();

    vertices.push_back( Vertex_pt( {  w - x, -h - y, 0 }, { 1, 1 } ) );
    vertices.push_back( Vertex_pt( { -w - x, -h - y, 0 }, { 0, 1 } ) );
    vertices.push_back( Vertex_pt( {  w - x,  h - y, 0 }, { 1, 0 } ) );
    vertices.push_back( Vertex_pt( { -w - x, -h - y, 0 }, { 0, 1 } ) );
    vertices.push_back( Vertex_pt( {  w - x,  h - y, 0 }, { 1, 0 } ) );
    vertices.push_back( Vertex_pt( { -w - x,  h - y, 0 }, { 0, 0 } ) );

    _token = _vao.add_vertices( std::move( vertices ) );
    _vao.add_render_static( _token.get_non_owner() );
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
