// Header
#include "spriterenderer.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void SpriteRenderer::set_entity( weak<Entity> pEntity )
{
    _entity = pEntity;
}

void SpriteRenderer::on_init( RenderEngine& pRenderEngine )
{
    _shader    = pRenderEngine.get_shader( "builtin_texture" );
    _texture   = pRenderEngine.get_texture( "res/textures/dev/128.png" );
    _material  = pRenderEngine.add_material( "sprite_test_material", make_owner<Material>( _shader, _texture ) );

    _vao = make_owner<VertexArray<Vertex_pt>>();
    
    vector<Vertex_pt> vertices = vector<Vertex_pt>();
    vertices.push_back( Vertex_pt( { 1, 0, -0.5 },  { 1, 1 } ) );
    vertices.push_back( Vertex_pt( { 0, 0, -0.5 },  { 0, 1 } ) );
    vertices.push_back( Vertex_pt( { 1, 1, -0.5 },  { 1, 0 } ) );
    vertices.push_back( Vertex_pt( { 0, 0, -0.5 },  { 0, 1 } ) );
    vertices.push_back( Vertex_pt( { 1, 1, -0.5 },  { 1, 0 } ) );
    vertices.push_back( Vertex_pt( { 0, 1, -0.5 },  { 0, 0 } ) );
    
    _token = _vao->add_vertices( std::move( vertices ) );
    _vao->add_render_static( _token.get_non_owner() );
}

void SpriteRenderer::on_render( RenderEngine& pRenderEngine, Camera& pCamera, Matrix4f& pProjViewMat, float pInterpolation )
{
    // Interpolate transform, as we are between a calculated tick and a future tick
    Vector3f        position = Vector3f::lerp( _entity->lastPosition, _entity->position, pInterpolation );
    Vector3f        scale    = Vector3f::lerp( _entity->lastScale, _entity->scale, pInterpolation );
    Quaternion4f    rotation = Quaternion4f::slerp( _entity->lastRotation, _entity->rotation, pInterpolation );

    Matrix4f        matPos      = Matrix4f::translation( position );
    Matrix4f        matScale    = Matrix4f::scaling( scale );
    Matrix4f        matRot      = Quaternion4f::to_rotation_mat4f( rotation );

    Matrix4f        world = (matScale * matRot) * matPos;

    // Set the world x view x projection matrix
    Matrix4f wvp = pProjViewMat * world;
    _material->get_shader()->set_vertex_uniform( Uniform::WORLD_VIEW_PROJ_MATRIX, wvp );

    _material->bind();
    _vao->render();
}

void SpriteRenderer::on_cleanup( RenderEngine& pRenderEngine )
{
    _vao.destroy();
    _token.destroy();
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
