// Header
#include "creature.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



void Creature::on_update()
{
}

void Creature::create_full_snapshot( vector<byte>& v, NetVarType type )
{
    Entity::create_full_snapshot( v, type );

    // SHARED
    __net_write( v, NetVarID::Creature_health );
    __net_write( v, health );

    __net_write( v, NetVarID::Creature_name );
    __net_write( v, name );

    // SELF
    if ( type == SELF ) {
        __net_write( v, NetVarID::Creature_stamina );
        __net_write( v, stamina );
    }
}

void Creature::create_delta_snapshot( vector<byte>&, Entity &, NetVarType )
{
}

void Creature::update_from_snapshot( map<int32, vector<byte>> )
{
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
