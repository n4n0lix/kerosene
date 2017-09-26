// Header
#include "spriterenderer.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SpriteRenderer::SpriteRenderer() : Renderer()
{

}

void SpriteRenderer::set_gameobject( weak<GameObject> gameobject )
{
    _gameObject = gameobject;
}

void SpriteRenderer::on_init()
{
    _shader    = get_renderengine()->get_shader( "builtin_texture" );
    _texture   = get_renderengine()->get_texture( "res/textures/dev/128.png" );
    _material  = get_renderengine()->add_material( "sprite_test_material", make_owner<Material>( _shader, _texture ) );

    _vao = make_owner<VertexArray<Vertex_pt>>(Vertex_pt().layout());
    
    vector<Vertex_pt> vertices = vector<Vertex_pt>();
    vertices.push_back( Vertex_pt( Vector3f( 1, 0, -.5 ), Vector2f( 1.0f, 1.0f ) ) );
    vertices.push_back( Vertex_pt( Vector3f( 0, 0, -.5 ), Vector2f( 0.0f, 1.0f ) ) );
    vertices.push_back( Vertex_pt( Vector3f( 1, 1, -.5 ), Vector2f( 1.0f, 0.0f ) ) );
    vertices.push_back( Vertex_pt( Vector3f( 0, 0, -.5 ), Vector2f( 0.0f, 1.0f ) ) );
    vertices.push_back( Vertex_pt( Vector3f( 1, 1, -.5 ), Vector2f( 1.0f, 0.0f ) ) );
    vertices.push_back( Vertex_pt( Vector3f( 0, 1, -.5 ), Vector2f( 0.0f, 0.0f ) ) );

    _token = _vao->add_vertices( std::move( vertices ) );
    _vao->add_render_static( _token.get_non_owner() );
}

void SpriteRenderer::on_render( weak<Camera> cam, Matrix4f proj_view )
{
    Matrix4f wvp = proj_view *_gameObject->transform.to_mat4f();
    _material->get_shader()->set_vertex_uniform( Uniform::WORLD_VIEW_PROJ_MATRIX, wvp );
    _material->bind();
    _vao->render();
}

void SpriteRenderer::on_cleanup()
{
    _vao.destroy();
    _token.destroy();
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
