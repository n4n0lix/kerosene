#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <exception>

// Other Includes

// Internal Includes
#include "_global.h"
#include "entity.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN



enum EntityClass {
    clEntity = 0,
    clCreature   = 1
};

class LogicEngine
{

public:
			LogicEngine();
            ~LogicEngine() = default;

    void on_start();
    void on_tick_start();
    void on_shutdown();

    void on_gamestate_end();

    weak<Entity>            add_entity( owner<Entity> );
    owner<Entity>           remove_entity( weak<Entity> );
    vector<weak<Entity>>&   get_entities();

    uint64 current_tick();
    uint64 ticks_elapsed_since( uint64 );


private:
    uint64 _tick;
    uint64 _lastTick;

    // Current Snapshot
    vector<owner<Entity>> _entityOwners;
    vector<weak<Entity>>  _entities;

    // Snapshot History
    vector<Entity>        _snapshot;


    static IDGen ENTITY_ID_GENERATOR;
};

ENGINE_NAMESPACE_END

