#pragma once

// Std-Includes
#include <iostream>

// Other Includes
#include "gamestate.h"
#include "spriterenderer.h"
#include "tilemaprenderer.h"
#include "camera.h"
#include "controllable.h"
#include "playercontroller.h"
#include "transform.h"
#include "_gamedef.h"

#include "player_spawner.h"
#include "tilemap_spawner.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using namespace ENGINE_NAMESPACE;

class TestGameState : public GameState
{

public:
            TestGameState() = default;
            virtual ~TestGameState();

protected:
    void on_start()         override;
    void on_update()        override;
    void on_frame_start()   override;
    void on_end()           override;

private:
    Entity    spawn_ui( weak<Scene> );

    bool moveCamLeft;
    bool moveCamRight;
    bool moveCamUp;
    bool moveCamDown;

    weak<Scene>    _mainScene;
    weak<Camera2D> _mainCamera;
    Entity   _player;
    Entity   _tilemap;

    weak<Scene>    _uiScene;
    weak<Camera2D> _uiCamera;
    Entity   _ui;
    weak<TextRenderer> _fpsText;

};
