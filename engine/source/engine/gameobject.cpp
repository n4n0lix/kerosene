// Header
#include "gameobject.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GameObject::GameObject() : _id(ID_GENERATOR.new_id())
{
}

GameObject::~GameObject()
{
	ID_GENERATOR.release_id(_id);
}

void GameObject::set_rendercomponent(owner<RenderComponent> comp)
{
	_render = move(comp);
}

RenderComponent* GameObject::get_rendercomponent()
{
	return _render.get();
}

void GameObject::destroy_at_tick_end()
{
	_destroyAtTickEnd = true;
}

bool GameObject::shall_be_destroyed_at_tick_end()
{
	return _destroyAtTickEnd;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

IDGen GameObject::ID_GENERATOR = IDGen();

ENGINE_NAMESPACE_END
