#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "gameobject.h"
#include "owner_list.h"
#include "list.h"

#include "renderengine.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

enum GameStateStatus {
    READY,      /* Not Running */
    RUNNING,    /* Running */
    FINISHED    /* Running, but finished */
};

class GameState
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
public:
            explicit GameState();

    void start();
    void update();
    void finish();
    void end();

    GameStateStatus         get_status() const;

	void				    add_gameobject(owner<GameObject> gameObject);
    owner<GameObject>       remove_gameobject(GameObject* gameObject);
	list<GameObject*>	    get_gameobjects();

    owner<GameState>        take_next_gamestate();
    void                    give_next_gamestate(owner<GameState> next);

    RenderEngine*           get_renderengine();
    void                    set_renderengine(RenderEngine* render);

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    virtual void on_start() = 0;
    virtual void on_update() = 0;
    virtual void on_end() = 0;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GameStateStatus				_status;

    owner<GameState>			_nextGameState;
	owner_list<GameObject>      _gameObjectsOwners;
	list<GameObject*>			_gameObjects;
    RenderEngine*               _renderEngine;

};

ENGINE_NAMESPACE_END
