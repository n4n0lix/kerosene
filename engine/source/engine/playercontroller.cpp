#include "stdafx.h"
#include "playercontroller.h"

ENGINE_NAMESPACE_BEGIN

PlayerController::PlayerController( weak<Entity> e ) : _entity(e)
{
}

void PlayerController::set_entity( weak<Entity> entity )
{
    _entity = entity;
}

void PlayerController::update( vector<KeyEvent>& keys, vector<CharEvent>& chars, vector<MouseEvent>& mouse )
{
    if ( _entity.is_ptr_usable() && _entity->has_component( ctype_Controllable ) ) {
        Controllable& controllable = (Controllable&)_entity->get_component( ctype_Controllable );

        for ( auto& event : keys ) {
            if ( event.is_consumed() ) continue;

            handleWASD( controllable, event );
        }
    }
}

void PlayerController::handleWASD( Controllable& ctrl, KeyEvent& event )
{
    if ( !event.state_switched() ) return;

    int32 key = event.key();

    if ( key == Key::W || key == Key::A || key == Key::S || key == Key::D ) {
        unique<CmdMove> cmd = make_unique<CmdMove>();
        cmd->started = event.pressed();

        switch ( event.key() )
        {
        case Key::W: cmd->type = MOVE_UP; break;
        case Key::A: cmd->type = MOVE_LEFT; break;
        case Key::S: cmd->type = MOVE_DOWN; break;
        case Key::D: cmd->type = MOVE_RIGHT; break;
        }

        ctrl.commandQ.emplace_back( std::move( cmd ) );

        event.consume();
    }
}

ENGINE_NAMESPACE_END
