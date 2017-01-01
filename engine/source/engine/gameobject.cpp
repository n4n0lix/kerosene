// Header
#include "gameobject.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GameObject::GameObject()
{
}

void GameObject::add_child(u_ptr<GameObject> child)
{
    child->_parent = this;
    _children.add( move(child) );
}

bool GameObject::is_child(GameObject* child)
{
    return _children.contains( child );
}

u_ptr<GameObject> GameObject::remove_child(GameObject* child)
{
    if (is_child( child )) {
        child->_parent = nullptr;
        return move( _children.extract( child ) );
    }

    return nullptr;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END


