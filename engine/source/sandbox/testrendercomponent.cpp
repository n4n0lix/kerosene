// Header
#include "testrendercomponent.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TestRenderComponent::TestRenderComponent()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Protected                       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TestRenderComponent::on_init()
{
	RenderEngine* engine = get_renderengine();

	_materialDiff = make_shared<Material>( engine->load_shader("builtin_diffuse") );
	_materialTex  = make_shared<Material>( engine->load_shader("builtin_texture"),
										   engine->load_texture("res/textures/dev/128.png") );

	list<Vertex_pc> vertices1 = list<Vertex_pc>();
	vertices1.add(Vertex_pc(Vector3f(-1, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices1.add(Vertex_pc(Vector3f( 0, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
	vertices1.add(Vertex_pc(Vector3f(-.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	_tokenTriangle1 = engine->add_vertices(_materialDiff, vertices1);

	list<Vertex_pc> vertices2 = list<Vertex_pc>();
	vertices2.add(Vertex_pc(Vector3f(0, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices2.add(Vertex_pc(Vector3f(1, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
	vertices2.add(Vertex_pc(Vector3f(.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	_tokenTriangle2 = engine->add_vertices(_materialDiff, vertices2);

	list<Vertex_pc> vertices3 = list<Vertex_pc>();
	vertices3.add(Vertex_pc(Vector3f(-1.0, 0, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices3.add(Vertex_pc(Vector3f( 0.0, 0, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
	vertices3.add(Vertex_pc(Vector3f(-0.5, 1, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	_tokenTriangle3 = engine->add_vertices(_materialDiff, vertices3);

	engine->add_render(_tokenTriangle1);
	engine->add_render(_tokenTriangle2);
	engine->add_render(_tokenTriangle3);


	list<Vertex_pt> vertices4 = list<Vertex_pt>();
	vertices4.add(Vertex_pt(Vector3f(1, 0, -.5), Vector2f(1.0f, 1.0f)));
	vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
	vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));
	vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
	vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));
	vertices4.add(Vertex_pt(Vector3f(0, 1, -.5), Vector2f(0.0f, 0.0f)));
	_tokenTriangle4 = engine->add_vertices(_materialTex, vertices4);

	engine->add_render(_tokenTriangle4);
}

void TestRenderComponent::on_render()
{

}

void TestRenderComponent::on_deinit()
{
	RenderEngine* engine = get_renderengine();

	engine->remove_render(_tokenTriangle1);
	engine->remove_render(_tokenTriangle2);
	engine->remove_render(_tokenTriangle3);
	engine->remove_render(_tokenTriangle4);

	engine->remove_vertices(_tokenTriangle1);
	engine->remove_vertices(_tokenTriangle2);
	engine->remove_vertices(_tokenTriangle3);
	engine->remove_vertices(_tokenTriangle4);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END