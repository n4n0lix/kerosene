#include "stdafx.h"
#include "controllable.h"

ENGINE_NAMESPACE_BEGIN

Controllable::Controllable() : 
    Component( ctype_Controllable ),
    health( 0 ), 
    stamina( 0 ), 
    name( "Unnamed" ), 
    moveSpeed( 1 ), 
    moveUp( false ), 
    moveDown( false ), 
    moveLeft( false ), 
    moveRight( false )
{
}

ENGINE_NAMESPACE_END


