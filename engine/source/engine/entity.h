#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "_meta.h"

#include "idgen.h"
#include "netvar.h"
#include "nethelper.h"

#include "transform.h"
#include "owner.h"

#define NET_GLOBAL_VARS public
#define NET_PLAYER_VARS public
#define LOCAL_VARS public


ENGINE_NAMESPACE_BEGIN

struct Entity
{
                    Entity();
    virtual         ~Entity();

    virtual void    on_update();

    virtual void    create_full_snapshot( vector<byte>&, NetVarType );
    virtual void    create_delta_snapshot( vector<byte>&, Entity&, NetVarType );
    virtual void    update_from_snapshot( map<int32, vector<byte>> );

NET_GLOBAL_VARS:
    uint32    uid;
    Transform transform;
    
NET_PLAYER_VARS:

LOCAL_VARS:
    Transform lastTransform;

};


ENGINE_NAMESPACE_END
