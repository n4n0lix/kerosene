#include "world.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

World::World() : _gameObjects(UniquePtrVector<GameObject>())
{
}

void World::add(u_ptr<GameObject> gameObject)
{
	_gameObjects.add(move(gameObject));
}


u_ptr<GameObject> World::remove(GameObject* gameObject)
{
	return _gameObjects.extract( gameObject );
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_END

