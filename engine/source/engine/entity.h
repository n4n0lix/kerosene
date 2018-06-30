#pragma once

// Std-Includes
#include <atomic>
// Other Includes

// Internal Includes
#include "_global.h"
#include "idgen.h"

ENGINE_NAMESPACE_BEGIN

typedef uint64 entity_id;

#define GLOBAL public
#define PLAYER public
#define LOCAL public

// ENTITY
class Entity
{
public:
  static Entity New();
  static Entity None;

  Entity();
  explicit Entity(entity_id _id);

  entity_id id();

  // COMPONENT
  template<typename COMPONENT>
  bool has() {
    return COMPONENT::get_all_components().contains(_id);
  }

  template<typename COMPONENT>
  COMPONENT& add() {
    COMPONENT comp = COMPONENT();
    comp.entity = *this;
    COMPONENT::get_all_components().emplace(_id, std::move(comp));

    return get<COMPONENT>();
  }

  template<typename COMPONENT>
  COMPONENT& get() {
    return COMPONENT::get_all_components().access(_id);
  }

  template<typename COMPONENT>
  COMPONENT& remove() {
    return COMPONENT::get_all_components().remove(_id);
  }

private:
  entity_id _id;

  static std::atomic<entity_id> NEXT_ID;
  static std::vector<entity_id> ALL_ENTITIES;
};

ENGINE_NAMESPACE_END