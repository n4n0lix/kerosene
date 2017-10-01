// Header
#include "entity.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

META_CLASS_REGISTER(0, Entity)

//bool __Entity_Register() {
//    MetaObject mobj = MetaObject();
//    mobj.id = 0;
//    mobj.name = "Entity";
//    function<void*(void)> _new = []() { return new Entity(); };
//    mobj.newInstance = _new;
//    Meta::instance().register_meta(mobj);
//    return true;
//}
//bool  Entity::__meta_reg = __Entity_Register();
//string Entity::__meta_name() { return "Entity"; }

Entity::Entity()
{
    uid = 0;
    transform   = Transform();
}

Entity::~Entity()
{

}

void Entity::create_full_snapshot( vector<byte>& v, NetVarType type )
{
    // SHARED
    __net_write( v, NetVarID::Entity_uid );
    __net_write( v, uid );

    __net_write( v, NetVarID::Entity_transform );
    __net_write( v, transform.position );

    // SELF
    if ( type == SELF ) {

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


