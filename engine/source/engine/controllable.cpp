#include "stdafx.h"
#include "controllable.h"

ENGINE_NAMESPACE_BEGIN

void CControllable::update( float delta ) {
    if ( entity.has<CTransform>() ) {
        Vector2f dirSpeed = Vector2f( 0, 0 );

        if ( moveUp )    dirSpeed.y += 1;
        if ( moveDown )  dirSpeed.y -= 1;
        if ( moveLeft )  dirSpeed.x -= 1;
        if ( moveRight ) dirSpeed.x += 1;

        dirSpeed = dirSpeed.normalized() * moveSpeed * delta;


        CTransform& transform = entity.get<CTransform>();

        transform.position.x += dirSpeed.x;
        transform.position.y += dirSpeed.y;
    }
}

ENGINE_NAMESPACE_END
