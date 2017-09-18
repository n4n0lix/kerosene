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

GameStateStatus GameState::get_status() const
{
    return _status;
}

void GameState::add_gameobject(owner<GameObject> gameObject)
{
	_gameObjects.push_back( gameObject.get_non_owner() );
    _gameObjectsOwners.push_back( std::move( gameObject ) );
}

owner<GameObject> GameState::remove_gameobject(weak<GameObject> gameObject)
{
    std::remove( _gameObjects.begin(), _gameObjects.end(), gameObject );
	return extract_owner( _gameObjectsOwners, gameObject );
}

/**
 * Returns all gameobjects of this gamestate.
 */
vector<weak<GameObject>> GameState::get_gameobjects()
{
	return _gameObjects;
}

/**
 * Gives ownership over the next gamestate.
 */
owner<GameState>    GameState::take_next_gamestate()
{
    return std::move( _nextGameState );
}

/**
 * Takes ownership of the next gamestate.
 */
void  GameState::give_next_gamestate(owner<GameState> next)
{
    _nextGameState = std::move( next );
}

/**
 * Returns the renderengine. This only returns a valid object if 
 * the gamestate is the current gamestate used by the engine.
 */
weak<RenderEngine> GameState::get_renderengine()
{
    return _renderEngine;
}

 weak<InputEngine> GameState::get_inputengine()
 {
     return _inputEngine;
 }

 void GameState::set_inputengine( weak<InputEngine> input )
 {
     _inputEngine = input;
 }

/**
* Set the render engine for this gamestate.
*/
void GameState::set_renderengine(weak<RenderEngine> render)
{
    _renderEngine = render;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
