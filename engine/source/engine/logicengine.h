#pragma once

// Std-Includes
#include <exception>

// Other Includes

// Internal Includes
#include "_global.h"
#include "idgen.h"
#include "entitysystem.h"
#include "controllablesystem.h"


ENGINE_NAMESPACE_BEGIN

class LogicEngine
{
public:

    void on_start();
    void on_tick_start();
    void on_update(float delta);
    void on_shutdown();

    void on_gamestate_end();

    weak<Entity>            add_entity( owner<Entity> );
    owner<Entity>           remove_entity( weak<Entity> );
    vector<weak<Entity>>&   get_entities();

private:
    // Systems
    EntitySystem        entitySys;
    ControllableSystem  controllableSys;

    // Current Snapshot
    vector<owner<Entity>> _entityOwners;
    vector<weak<Entity>>  _entities;

    // Snapshot History
    vector<unique<Entity>> _snapshot;

    static IDGen ENTITY_ID_GENERATOR;
};

ENGINE_NAMESPACE_END

