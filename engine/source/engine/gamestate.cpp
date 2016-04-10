// Header
#include "gamestate.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GameState::GameState()
{
    _status = READY;
}

void GameState::start()
{
    _status = RUNNING;
    onStart();
}

void GameState::update()
{
    onUpdate();
}

void GameState::finish()
{
    _status = FINISHED;
}

void GameState::end()
{
    onEnd();
    _status = READY;
}

GameStateStatus GameState::getStatus() const
{
    return _status;
}

shared_ptr<GameState> GameState::getNext() const
{
    return _nextGameState;
}

void GameState::setNext(shared_ptr<GameState> next)
{
    _nextGameState = next;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
