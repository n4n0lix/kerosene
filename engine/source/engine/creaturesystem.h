#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "entitysystem.h"
#include "creature.h"

ENGINE_NAMESPACE_BEGIN

//
// SYSTEM
////////////////////////////////////////

struct Entity;

struct CreatureSystem
{
    void process_cmds( Creature&  );
    void update( Entity& , Creature& );

    Creature create_snapshot_full( Creature& );
    //Creature create_snapshot_delta( Creature& prev, Creature& src );
};

ENGINE_NAMESPACE_END

