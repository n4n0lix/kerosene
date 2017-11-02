#include "stdafx.h"
#include "controllable.h"

ENGINE_NAMESPACE_BEGIN

REGISTER_MIXIN( 1, Controllable )

void Controllable::update( float delta ) {
    if ( mixin::has<has_transform>( id ) ) {
        Vector2f dirSpeed = Vector2f( 0, 0 );

        if ( moveUp )    dirSpeed.y += 1;
        if ( moveDown )  dirSpeed.y -= 1;
        if ( moveLeft )  dirSpeed.x -= 1;
        if ( moveRight ) dirSpeed.x += 1;

        dirSpeed = dirSpeed.normalized() * moveSpeed * delta;


        has_transform& transform = mixin::access<has_transform>( id );

        transform.position.x += dirSpeed.x;
        transform.position.y += dirSpeed.y;
    }
}

ENGINE_NAMESPACE_END
