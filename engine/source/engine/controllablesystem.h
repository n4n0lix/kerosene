#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "entitysystem.h"
#include "controllable.h"
#include "component.h"

ENGINE_NAMESPACE_BEGIN

//
// SYSTEM
////////////////////////////////////////

struct Entity;

struct ControllableSystem
{

    void update( Entity& );
    void create_snapshot_full( Entity& dest, Entity& );
    void create_snapshot_delta( Entity& dest, Entity& prev, Entity& src );

    void add_command( uint32 entityId, unique<Command> );

private:
    void process_cmds( Controllable& );

    map<uint32, vector<unique<Command>>> commandQ;
};

ENGINE_NAMESPACE_END

