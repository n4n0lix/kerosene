#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "gameobject.h"

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
            ~GameState() = default;

    void start();
    void update();
    void finish();
    void end();

    GameStateStatus             get_status() const;

	void				        add_gameobject(owner<GameObject> gameObject);
    owner<GameObject>           remove_gameobject(weak<GameObject> gameObject);
    vector<weak<GameObject>>    get_gameobjects();

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
    vector<owner<GameObject>>   _gameObjectsOwners;
    vector<weak<GameObject>>	_gameObjects;
    RenderEngine*               _renderEngine;

};

ENGINE_NAMESPACE_END
