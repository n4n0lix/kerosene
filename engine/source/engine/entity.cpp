#include "entity.h"

ENGINE_NAMESPACE_BEGIN

Entity::Entity() : position( Vector3f( 0, 0, 0 ) ), scale( Vector3f( 1, 1, 1 ) ), rotation( Quaternion4f( 0, 0, 0, 1 ) )
{
}

bool Entity::has_component( ComponentType compType )
{
    return _components.count( compType ) > 0;
}

void Entity::add_component( unique<Component> component )
{
    if ( has_component( component->type ) )
        _components.erase( component->type );

    _components.emplace( component->type, std::move( component ) );
}

Component& Entity::get_component( ComponentType compType ) {
    auto it = _components.find( compType );
    return *(it->second.get());
}

ENGINE_NAMESPACE_END


