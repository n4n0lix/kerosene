// Header
#include "testrenderer.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Protected                       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TestRenderer::on_init()
{
    weak<RenderEngine> engine = get_renderengine();

    weak<Shader>   s_diffuse = engine->get_shader( "builtin_diffuse" );
    _materialDiff = engine->add_material( "mat_diffuse", make_owner<Material>( s_diffuse ) );
    _batch_pc = make_owner<Batch<Vertex_pc>>( _materialDiff );

    vector<Vertex_pc> vertices1 = vector<Vertex_pc>();
    vertices1.push_back( Vertex_pc( Vector3f( -1, -1, -.5 ), Vector4f( 1.0f, 0.0f, 0.0f, 1.0f ) ) );
    vertices1.push_back( Vertex_pc( Vector3f( 0, -1, -.5 ),  Vector4f( 1.0f, 1.0f, 0.0f, 1.0f ) ) );
    vertices1.push_back( Vertex_pc( Vector3f( -.5, 0, -.5 ), Vector4f( 0.0f, 1.0f, 0.0f, 1.0f ) ) );
    _tokenTriangle1 = _batch_pc->add_vertices( std::move( vertices1 ) );
    _batch_pc->add_render( _tokenTriangle1.get_non_owner() );

    vector<Vertex_pc> vertices2 = vector<Vertex_pc>();
    vertices2.push_back( Vertex_pc( Vector3f( 0, -1, -.5 ), Vector4f( 1.0f, 0.0f, 0.0f, 1.0f ) ) );
    vertices2.push_back( Vertex_pc( Vector3f( 1, -1, -.5 ), Vector4f( 1.0f, 1.0f, 0.0f, 1.0f ) ) );
    vertices2.push_back( Vertex_pc( Vector3f( .5, 0, -.5 ), Vector4f( 0.0f, 1.0f, 0.0f, 1.0f ) ) );
    _tokenTriangle2 = _batch_pc->add_vertices( std::move( vertices2 ) );
    _batch_pc->add_render( _tokenTriangle2.get_non_owner() );

    vector<Vertex_pc> vertices3 = vector<Vertex_pc>();
    vertices3.push_back( Vertex_pc( Vector3f( -1.0, 0, -.5 ), Vector4f( 1.0f, 0.0f, 0.0f, 1.0f ) ) );
    vertices3.push_back( Vertex_pc( Vector3f( 0.0, 0, -.5 ),  Vector4f( 1.0f, 1.0f, 0.0f, 1.0f ) ) );
    vertices3.push_back( Vertex_pc( Vector3f( -0.5, 1, -.5 ), Vector4f( 0.0f, 1.0f, 0.0f, 1.0f ) ) );
    _tokenTriangle3 = _batch_pc->add_vertices( std::move( vertices3 ) );
    _batch_pc->add_render( _tokenTriangle3.get_non_owner() );


    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    weak<Shader>   s_texture = engine->get_shader( "builtin_texture" );
    weak<Texture>  t_128 = engine->add_texture( "dev_128", engine->load_texture( "res/textures/dev/128.png" ) );
    _materialTex = engine->add_material( "mat_tex128", make_owner<Material>( s_texture, t_128 ) );
    _batch_pt = make_owner<Batch<Vertex_pt>>( _materialTex );

    vector<Vertex_pt> vertices4 = vector<Vertex_pt>();
    vertices4.push_back( Vertex_pt( Vector3f( 1, 0, -.5 ), Vector2f( 1.0f, 1.0f ) ) );
    vertices4.push_back( Vertex_pt( Vector3f( 0, 0, -.5 ), Vector2f( 0.0f, 1.0f ) ) );
    vertices4.push_back( Vertex_pt( Vector3f( 1, 1, -.5 ), Vector2f( 1.0f, 0.0f ) ) );
    vertices4.push_back( Vertex_pt( Vector3f( 0, 0, -.5 ), Vector2f( 0.0f, 1.0f ) ) );
    vertices4.push_back( Vertex_pt( Vector3f( 1, 1, -.5 ), Vector2f( 1.0f, 0.0f ) ) );
    vertices4.push_back( Vertex_pt( Vector3f( 0, 1, -.5 ), Vector2f( 0.0f, 0.0f ) ) );
    _tokenTriangle4 = _batch_pt->add_vertices( std::move( vertices4 ) );

    _batch_pt->add_render( _tokenTriangle4.get_non_owner() );
}

void TestRenderer::on_render()
{
    _batch_pc->render();
    _batch_pt->render();
}

void TestRenderer::on_cleanup()
{
    _batch_pc->remove_vertices( std::move( _tokenTriangle1 ) );
    _batch_pc->remove_vertices( std::move( _tokenTriangle2 ) );
    _batch_pc->remove_vertices( std::move( _tokenTriangle3 ) );
    _batch_pc.destroy();

    _batch_pt->remove_vertices( std::move( _tokenTriangle4 ) );
    _batch_pt.destroy();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END