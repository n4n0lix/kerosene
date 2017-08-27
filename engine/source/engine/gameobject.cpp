// Header
#include "gameobject.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GameObject::GameObject() : _id(ID_GENERATOR.get())
{
}

GameObject::~GameObject()
{
	ID_GENERATOR.remove(_id);
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

IdGenerator GameObject::ID_GENERATOR = IdGenerator();

ENGINE_NAMESPACE_END
