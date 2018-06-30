#include "stdafx.h"
#include "renderer.h"

ENGINE_NAMESPACE_BEGIN

Renderer::Renderer()
  : _initialized(false)
{

}

Renderer::Renderer(Entity entity)
  : Renderer()
{
  set_entity( entity );
}

void Renderer::init( RenderEngine& engine )
{
	on_init( engine );
	_initialized = true;
}

void Renderer::render( RenderEngine& engine, Camera& cam, Matrix4f& view_proj, float interpolation )
{
    on_render( engine, cam, view_proj, interpolation );
}

void Renderer::cleanup( RenderEngine& engine )
{
	on_cleanup( engine );
	_initialized = false;
}

bool Renderer::is_initialized()
{
	return _initialized;
}

Entity Renderer::get_entity() const
{
    return _entity;
}

void Renderer::set_entity(Entity pEntity)
{
  _entity = pEntity;
}

int32  Renderer::render_layer() const {
    return _renderlayer;
}

void Renderer::set_render_layer( int32 renderlayer ) {
    _renderlayer = renderlayer;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
