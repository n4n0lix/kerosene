#include "entitysystem.h"

ENGINE_NAMESPACE_BEGIN

Entity::Entity() : position( Vector3f( 0, 0, 0 ) ), scale( Vector3f( 1, 1, 1 ) ), rotation( Quaternion4f( 0, 0, 0, 1 ) )
{
}

void EntitySystem::update( Entity& entity )
{
    entity.lastPosition  = entity.position;
    entity.lastScale     = entity.scale;
    entity.lastRotation  = entity.rotation;
}

Entity EntitySystem::create_snapshot_full( Entity& entity )
{
    Entity snapshot;

    snapshot.id = entity.id;
    snapshot.position = entity.position;
    snapshot.scale    = entity.scale;
    snapshot.rotation = entity.rotation;

    return std::move( snapshot );
}

ENGINE_NAMESPACE_END


