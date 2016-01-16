#ifndef TESTGAMESTATE_H
#define TESTGAMESTATE_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>

// Other Includes
#include "gamestate.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using namespace ENGINE_NAMESPACE;

class TestGameState : public GameState
{

public:
    explicit TestGameState();

protected:
    virtual void onStart();
    virtual void onUpdate();
    virtual void onEnd();
};

#endif // TESTGAMESTATE_H
