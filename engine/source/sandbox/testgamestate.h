#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>

// Other Includes
#include "gamestate.h"
#include "spriterenderer.h"
#include "camera.h"

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
    weak<Scene>    _scene;
    weak<Camera>   _camera;
    weak<Entity>   _entity;
    weak<SpriteRenderer> _renderer;

    bool _aDown;
    bool _dDown;
    bool _sDown;
    bool _wDown;
};
