#include "stdafx.h"
#include "playercontroller.h"

ENGINE_NAMESPACE_BEGIN

PlayerController::PlayerController( weak<Entity> e ) : entity(e)
{
}

void PlayerController::set_entity( weak<Entity> pEntity )
{
    entity = pEntity;
}

void PlayerController::update( std::vector<KeyEvent>& keys, std::vector<CharEvent>& chars, std::vector<MouseEvent>& mouse )
{
    Guard( entity ) return;
    Guard( entity->has<Controllable>() ) return;

    Controllable& ctrl = entity->access<Controllable>();

    for ( auto& key : keys ) {
        handleWASD( ctrl, key );
    }
}

void PlayerController::handleWASD( Controllable& ctrl, KeyEvent& event )
{
    if ( !event.state_changed() ) return;

    Key key = event.key();

    if ( key == Key::W || key == Key::A || key == Key::S || key == Key::D ) {
        bool* moveDir = nullptr;
        switch ( key )
        { 
            case Key::W: moveDir = &ctrl.moveUp;    break;
            case Key::A: moveDir = &ctrl.moveLeft;  break;
            case Key::S: moveDir = &ctrl.moveDown;  break;
            case Key::D: moveDir = &ctrl.moveRight; break;
        }

        if (moveDir != nullptr ) 
            *moveDir = event.pressed();

        event.consume();
    }
}

ENGINE_NAMESPACE_END
