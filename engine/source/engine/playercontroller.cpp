#include "stdafx.h"
#include "playercontroller.h"

ENGINE_NAMESPACE_BEGIN

PlayerController::PlayerController( Entity e ) : entity(e)
{
}

void PlayerController::set_entity( Entity pEntity )
{
    entity = pEntity;
}

void PlayerController::update( std::vector<KeyEvent>& keys, std::vector<CharEvent>& chars, std::vector<MouseEvent>& mouse )
{
    if ( !entity.has<CControllable>() ) return;

    CControllable& ctrl = entity.get<CControllable>();

    for ( auto& key : keys ) {
        handleWASD( ctrl, key );
    }
}

void PlayerController::handleWASD( CControllable& ctrl, KeyEvent& event )
{
    if ( !event.state_changed() ) return;

    Key key = event.key();

    bool* moveDir = nullptr;
    switch ( key )
    { 
        case Key::Up:
        case Key::W: 
            moveDir = &ctrl.moveUp;    break;

        case Key::Left:
        case Key::A: 
            moveDir = &ctrl.moveLeft;  break;

        case Key::Down:
        case Key::S: 
            moveDir = &ctrl.moveDown;  break;

        case Key::Right:
        case Key::D: 
            moveDir = &ctrl.moveRight; break;

        default:
            return;
    }

    if (moveDir != nullptr ) 
        *moveDir = event.pressed();

    event.consume();
}

ENGINE_NAMESPACE_END
