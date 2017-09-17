// Header
#include "testrendercomponent.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Protected                       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TestRenderComponent::on_init()
{
	RenderEngine* engine = get_renderengine();

    weak<Shader>   s_diffuse   = engine->get_shader("builtin_diffuse");
    weak<Shader>   s_texture   = engine->get_shader("builtin_texture");

    weak<Texture>  t_128 = engine->add_texture("dev_128", engine->load_texture("res/textures/dev/128.png"));

	_materialDiff = engine->add_material( "mat_diffuse", make_owner<Material>( s_diffuse ));
	_materialTex  = engine->add_material( "mat_tex128",  make_owner<Material>( s_texture, t_128 ));

	list<Vertex_pc> vertices1 = list<Vertex_pc>();
	vertices1.add(Vertex_pc(Vector3f(-1, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices1.add(Vertex_pc(Vector3f( 0, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
	vertices1.add(Vertex_pc(Vector3f(-.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	_tokenTriangle1 = engine->add_vertices(_materialDiff, std::move( vertices1 ));

	list<Vertex_pc> vertices2 = list<Vertex_pc>();
	vertices2.add(Vertex_pc(Vector3f(0, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices2.add(Vertex_pc(Vector3f(1, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
	vertices2.add(Vertex_pc(Vector3f(.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	_tokenTriangle2 = engine->add_vertices(_materialDiff, std::move( vertices2 ));

	list<Vertex_pc> vertices3 = list<Vertex_pc>();
	vertices3.add(Vertex_pc(Vector3f(-1.0, 0, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices3.add(Vertex_pc(Vector3f( 0.0, 0, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
	vertices3.add(Vertex_pc(Vector3f(-0.5, 1, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	_tokenTriangle3 = engine->add_vertices(_materialDiff, std::move( vertices3 ));

	engine->add_render( _tokenTriangle1.get_non_owner() );
	engine->add_render( _tokenTriangle2.get_non_owner() );
	engine->add_render( _tokenTriangle3.get_non_owner() );


	list<Vertex_pt> vertices4 = list<Vertex_pt>();
	vertices4.add(Vertex_pt(Vector3f(1, 0, -.5), Vector2f(1.0f, 1.0f)));
	vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
	vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));
	vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
	vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));
	vertices4.add(Vertex_pt(Vector3f(0, 1, -.5), Vector2f(0.0f, 0.0f)));
	_tokenTriangle4 = engine->add_vertices(_materialTex, std::move( vertices4 ));

	engine->add_render( _tokenTriangle4.get_non_owner() );
}

void TestRenderComponent::on_render()
{

}

void TestRenderComponent::on_deinit()
{
	//RenderEngine* engine = get_renderengine();

	//engine->remove_render(_tokenTriangle1);
	//engine->remove_render(_tokenTriangle2);
	//engine->remove_render(_tokenTriangle3);
	//engine->remove_render(_tokenTriangle4);

	//engine->remove_vertices(_tokenTriangle1);
	//engine->remove_vertices(_tokenTriangle2);
	//engine->remove_vertices(_tokenTriangle3);
	//engine->remove_vertices(_tokenTriangle4);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END