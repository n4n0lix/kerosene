#pragma once

// Std-Includes
#include <exception>

// Other Includes

// Internal Includes
#include "_global.h"
#include "idgen.h"

#include "entity.h"
#include "mixins.h"
#include "transform.h"
#include "controllable.h"

ENGINE_NAMESPACE_BEGIN

class LogicEngine
{
public:

    void on_start();
    void on_tick_start();
    void on_update(float delta);
    void on_shutdown();

    void on_gamestate_end();

    weak<Entity>                add_entity( owner<Entity> );
    owner<Entity>               remove_entity( weak<Entity> );
    std::vector<weak<Entity>>&  get_entities();

private:
    // Current Snapshot
    std::vector<owner<Entity>> _entityOwners;
    std::vector<weak<Entity>>  _entities;

    static IDGen ENTITY_ID_GENERATOR;
};

ENGINE_NAMESPACE_END

