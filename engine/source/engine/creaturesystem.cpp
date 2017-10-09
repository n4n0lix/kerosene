#include "creaturesystem.h"
ENGINE_NAMESPACE_BEGIN

//
// SYSTEM
////////////////////////////////////////

void CreatureSystem::process_cmds( Creature& creature)
{
    for ( auto& command : creature.commandQ )
        if ( !(command->consumed) ) {
            if ( command->type == MOVE_UP ) {
                unique<CmdMove>& cmd = (unique<CmdMove>&) command;
                creature.moveUp = cmd->started;
            }
            if ( command->type == MOVE_DOWN ) {
                unique<CmdMove>& cmd = (unique<CmdMove>&) command;
                creature.moveDown = cmd->started;
            }
            if ( command->type == MOVE_LEFT ) {
                unique<CmdMove>& cmd = (unique<CmdMove>&) command;
                creature.moveLeft = cmd->started;
            }
            if ( command->type == MOVE_RIGHT ) {
                unique<CmdMove>& cmd = (unique<CmdMove>&) command;
                creature.moveRight = cmd->started;
            }
    }

    creature.commandQ.clear();
}

void CreatureSystem::update( Entity& entity, Creature& creature )
{
    process_cmds( creature );

    if ( creature.moveUp    ) 
        entity.position.y += creature.moveSpeed;
    if ( creature.moveDown  ) 
        entity.position.y -= creature.moveSpeed;
    if ( creature.moveLeft  ) 
        entity.position.x -= creature.moveSpeed;
    if ( creature.moveRight ) 
        entity.position.x += creature.moveSpeed;
}

Creature CreatureSystem::create_snapshot_full( Creature& orig )
{
    Creature snapshot;

    snapshot.health     = orig.health;
    snapshot.stamina    = orig.stamina;
    snapshot.name       = orig.name;
    snapshot.moveSpeed  = orig.moveSpeed;

    return std::move( snapshot );
}

//
// ADDITIONAL
////////////////////////////////////////

Command::Command() : type(UNKOWN), consumed(false) {}

CmdMove::CmdMove() : Command(), started(false) {}


ENGINE_NAMESPACE_END

