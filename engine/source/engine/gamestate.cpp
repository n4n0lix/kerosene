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
    on_start();
}

void GameState::update()
{
    on_update();
}

void GameState::finish()
{
    _status = FINISHED;
}

void GameState::end()
{
    on_end();
    _status = READY;
}

GameStateStatus     GameState::get_status() const
{
    return _status;
}

void                GameState::add_gameobject(owner<GameObject> gameObject)
{
	_gameObjects.add(gameObject.get());
	_gameObjectsOwners.add( move(gameObject) );
}

owner<GameObject>   GameState::remove_gameobject(GameObject* gameObject)
{
	_gameObjects.remove(gameObject);
	return _gameObjectsOwners.extract(gameObject);
}

/**
 * Returns all gameobjects of this gamestate.
 */
list<GameObject*> GameState::get_gameobjects()
{
	return _gameObjects;
}

/**
 * Gives ownership over the next gamestate.
 */
owner<GameState>    GameState::take_next_gamestate()
{
    return move( _nextGameState );
}

/**
 * Takes ownership of the next gamestate.
 */
void                GameState::give_next_gamestate(owner<GameState> next)
{
    _nextGameState = move( next );
}

/**
 * Returns the renderengine. This only returns a valid object if 
 * the gamestate is the current gamestate used by the engine.
 */
RenderEngine*   GameState::get_renderengine()
{
    return move( _renderEngine );
}

/**
* Set the render engine for this gamestate.
*/
void            GameState::set_renderengine(RenderEngine* render)
{
    _renderEngine = render;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
