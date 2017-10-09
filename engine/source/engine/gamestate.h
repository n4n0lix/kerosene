#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "entitysystem.h"

#include "renderengine.h"
#include "inputengine.h"
#include "logicengine.h"


ENGINE_NAMESPACE_BEGIN

enum GameStateStatus {
    READY,      /* Not Running */
    RUNNING,    /* Running */
    FINISHED    /* Running, but finished */
};

class GameState
{
public:
            explicit GameState();
            virtual ~GameState() = default;

    void start();
    void end();

    virtual void    on_update() {}
    virtual void    on_frame_start() {}
    virtual void    on_frame_end() {}

    GameStateStatus             get_status() const;

    owner<GameState>            take_next_gamestate();
    void                        give_next_gamestate( owner<GameState>);

    weak<RenderEngine>          get_renderengine();
    void                        set_renderengine( weak<RenderEngine> );

    weak<InputEngine>           get_inputengine();
    void                        set_inputengine( weak<InputEngine> );

    weak<LogicEngine>           get_logicengine();
    void                        set_logicengine( weak<LogicEngine> );

protected:
    virtual void on_start()       {}
    virtual void on_end()         {}

    void set_status( GameStateStatus status );

private:
    GameStateStatus				_status;

    owner<GameState>			_nextGameState;

    weak<RenderEngine>          _renderEngine;
    weak<InputEngine>           _inputEngine;
    weak<LogicEngine>           _logicEngine;
};

ENGINE_NAMESPACE_END
