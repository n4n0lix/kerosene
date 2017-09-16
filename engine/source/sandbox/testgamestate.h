#ifndef TESTGAMESTATE_H
#define TESTGAMESTATE_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>

// Other Includes
#include "gamestate.h"
#include "gameobject.h"
#include "testrendercomponent.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using namespace ENGINE_NAMESPACE;

class TestGameState : public GameState
{

public:
    TestGameState() = default;
    virtual ~TestGameState() = default;

protected:
    virtual void on_start();
    virtual void on_update();
    virtual void on_end();
};

#endif // TESTGAMESTATE_H
