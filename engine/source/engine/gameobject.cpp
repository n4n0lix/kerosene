// Header
#include "gameobject.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GameObject::GameObject() : activeHandles(vector<Handle*>())
{
}

GameObject::~GameObject()
{
	for (auto handle : activeHandles) {
		handle->invalidate();
	}
}

u_ptr<GameObject::Handle> GameObject::get_handle()
{
	u_ptr<Handle> handle = make_unique<Handle>(this);
	activeHandles.push_back(handle.get());
	return move(handle);
}

void GameObject::destroy()
{
	_destroy = true;
}

bool GameObject::shall_be_destroyed()
{
	return _destroy;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

atomic<uint64> GameObject::UID_COUNTER = 0;

//============================================================
//============================================================
//============================================================

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GameObject::Handle::Handle(GameObject* gameObject) : valid(false), gameObject(gameObject)
{

}

GameObject::Handle::~Handle()
{
	// If GameObject is alive (bcz wasn't invalidated yet) remove from its activeHandles
	if (valid) {
		vector<Handle*> vector = gameObject->activeHandles;
		vector.erase(std::remove(vector.begin(), vector.end(), this), vector.end());
	}
}

GameObject * GameObject::Handle::get()
{
	if (valid)
		return gameObject;

	return nullptr;
}

void GameObject::Handle::invalidate()
{
	valid = false;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
