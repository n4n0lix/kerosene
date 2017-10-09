#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#define GLOBAL_VARS public
#define PLAYER_VARS public
#define LOCAL_VARS  public


ENGINE_NAMESPACE_BEGIN

enum CmdType {
    // Meta
    UNKOWN,

    // Creature - Movement
    MOVE_UP, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT,
    TURN_TO_TARGET,

    // Chat
    CHAT_MSG,

    // UI
    UI_OPEN_INVENTORY
};

struct Command
{
    Command();

    CmdType  type;
    bool     consumed;
};

struct CmdMove : Command {
    CmdMove();

    bool started;
};

struct Creature
{
    Creature();

GLOBAL_VARS:
    int32           health;
    int32           stamina;
    string          name;
    float           moveSpeed;

PLAYER_VARS:

LOCAL_VARS:
    bool moveUp;
    bool moveDown;
    bool moveLeft;
    bool moveRight;

    vector<unique<Command>> commandQ;
};

ENGINE_NAMESPACE_END

