#include "stdafx.h"
#include "controllablesystem.h"

ENGINE_NAMESPACE_BEGIN

//
// SYSTEM
////////////////////////////////////////

void ControllableSystem::update( Entity& entity, float delta )
{
    if ( !entity.has_component( ComponentType::Controllable ) )
        return;

    Controllable& creature = (Controllable&) entity.get_component( ComponentType::Controllable );

    process_cmds( creature );

    if ( creature.moveUp    ) 
        entity.position.y += creature.moveSpeed * delta;
    if ( creature.moveDown  ) 
        entity.position.y -= creature.moveSpeed * delta;
    if ( creature.moveLeft  ) 
        entity.position.x -= creature.moveSpeed * delta;
    if ( creature.moveRight ) 
        entity.position.x += creature.moveSpeed * delta;
}

void ControllableSystem::create_snapshot_full( Entity& dest, Entity& src)
{
    // 1# Find Component
    if ( !src.has_component( ComponentType::Controllable ) )
        return;

    Controllable& cSrc = (Controllable&) src.get_component( ComponentType::Controllable );

    // 2# Create Snapshot
    owner<Controllable> cDest = make_owner<Controllable>();

    cDest->health     = cSrc.health;
    cDest->stamina    = cSrc.stamina;
    cDest->name       = cSrc.name;
    cDest->moveSpeed  = cSrc.moveSpeed;

    dest.add_component( std::move( cDest ) );
}

void ControllableSystem::process_cmds( Controllable& controlable )
{
    for ( auto& command : controlable.commandQ )
        if ( !(command->consumed) ) {
            if ( command->type == CmdType::MOVE_UP ) {
                controlable.moveUp = ((unique<CmdMove>&) command)->started;
            }
            if ( command->type == CmdType::MOVE_DOWN ) {
                controlable.moveDown = ((unique<CmdMove>&) command)->started;
            }
            if ( command->type == CmdType::MOVE_LEFT ) {
                controlable.moveLeft = ((unique<CmdMove>&) command)->started;
            }
            if ( command->type == CmdType::MOVE_RIGHT ) {
                controlable.moveRight = ((unique<CmdMove>&) command)->started;
            }
        }

    controlable.commandQ.clear();
}

//
// ADDITIONAL
////////////////////////////////////////

Command::Command() : type(CmdType::UNKOWN), consumed(false) {}

CmdMove::CmdMove() : Command(), started(false) {}


ENGINE_NAMESPACE_END

