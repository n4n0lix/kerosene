#include "entitysystem.h"

ENGINE_NAMESPACE_BEGIN

void EntitySystem::update( Entity& entity )
{
    entity.lastPosition  = entity.position;
    entity.lastScale     = entity.scale;
    entity.lastRotation  = entity.rotation;
}

void EntitySystem::create_snapshot_full( Entity& dest, Entity& src )
{
    dest.id = src.id;
    dest.position = src.position;
    dest.scale    = src.scale;
    dest.rotation = src.rotation;
}

ENGINE_NAMESPACE_END


