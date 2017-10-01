#include "_meta.h"

ENGINE_NAMESPACE_BEGIN

MetaObject& Meta::get_meta( string name ) 
{
    return classTableByString[name];
}

MetaObject & Meta::get_meta( uint16 id )
{
    return classTableByID[id];
}

ENGINE_NAMESPACE_END