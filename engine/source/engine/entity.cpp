// Header
#include "entity.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Entity::Entity()
{
    uid = 0;
    transform   = Transform();
}

Entity::~Entity()
{

}

void Entity::on_update()
{
    lastTransform = transform;
}

void Entity::create_full_snapshot( vector<byte>& v, NetVarType pType )
{
    // SHARED
    __net_write( v, NetVarID::Entity_uid );
    __net_write( v, uid );

    __net_write( v, NetVarID::Entity_transform );
    __net_write( v, transform.position );

    // SELF
    if ( pType == SELF ) {

    }
}

void Entity::create_delta_snapshot( vector<byte>&, Entity &, NetVarType )
{
}

void Entity::update_from_snapshot( map<int32, vector<byte>> )
{
}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END


