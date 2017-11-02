#include "stdafx.h"
#include "renderer.h"

ENGINE_NAMESPACE_BEGIN

Renderer::Renderer() : _initialized(false) {

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

weak<Entity> Renderer::get_entity()
{
    return _entity;
}

void Renderer::set_entity( weak<Entity> pEntity )
{
    _entity = pEntity;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
