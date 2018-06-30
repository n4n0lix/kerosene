#pragma once

// Std-Includes
#include <algorithm>

// Other Includes

// Internal Includes
#include "_global.h"
#include "compact_map.h"
#include "entity.h"

ENGINE_NAMESPACE_BEGIN

class Component : public noncopyable {
public:
  Entity  entity;

  virtual void    update( float delta ) = 0;
};

#define COMPONENT(NAME, PRIORITY) \
  class NAME : public Component { \
  public: \
		static compact_map<entity_id, NAME>& get_all_components() { \
		  static compact_map<entity_id, NAME> ALL_INSTANCES; \
		  return ALL_INSTANCES; \
		};

#define END };

ENGINE_NAMESPACE_END