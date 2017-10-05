#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "entity.h"


ENGINE_NAMESPACE_BEGIN

struct Creature : Entity
{
public:

                    Creature() = default;
    virtual         ~Creature() = default;

    virtual void    on_update();

    virtual void    create_full_snapshot( vector<byte>&, NetVarType ) override;
    virtual void    create_delta_snapshot( vector<byte>&, Entity&, NetVarType ) override;
    virtual void    update_from_snapshot( map<int32, vector<byte>> ) override;

NET_GLOBAL_VARS:
    int32 health;
    string name;

NET_PLAYER_VARS:
    int32 stamina;

LOCAL_VARS:

};

ENGINE_NAMESPACE_END

