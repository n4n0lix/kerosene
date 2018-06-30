#include "stdafx.h"
#include "entity.h"

ENGINE_NAMESPACE_BEGIN

std::atomic<entity_id> Entity::NEXT_ID = 1;
Entity Entity::None = Entity(0);

Entity Entity::New()
{
  return Entity(Entity::NEXT_ID++);
}

Entity::Entity()
  : _id(0) 
{

}

Entity::Entity(entity_id _id)
  : _id(_id)
{

}

entity_id Entity::id() {
  return _id;
}

ENGINE_NAMESPACE_END