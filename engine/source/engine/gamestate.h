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
            virtual ~GameState() = default;

    void start();
    void end();

    virtual void    on_update() {}
    virtual void    on_frame_start() {}
    virtual void    on_frame_end() {}

    GameStateStatus             get_status() const;

	void				        add_gameobject(owner<GameObject> gameObject);
    owner<GameObject>           remove_gameobject(weak<GameObject> gameObject);
    vector<weak<GameObject>>    get_gameobjects();

    owner<GameState>            take_next_gamestate();
    void                        give_next_gamestate(owner<GameState> next);

    weak<RenderEngine>          get_renderengine();
    void                        set_renderengine(weak<RenderEngine> render);

    weak<InputEngine>           get_inputengine();
    void                        set_inputengine( weak<InputEngine> input );

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    virtual void on_start()       {}
    virtual void on_end()         {}

    void set_status( GameStateStatus status );

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GameStateStatus				_status;

    owner<GameState>			_nextGameState;
    vector<owner<GameObject>>   _gameObjectsOwners;
    vector<weak<GameObject>>	_gameObjects;

    weak<RenderEngine>          _renderEngine;
    weak<InputEngine>           _inputEngine;
};

ENGINE_NAMESPACE_END
