// Header
#include "testgamestate.h"
using namespace ENGINE_NAMESPACE;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TestGameState::TestGameState() : GameState()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Protected                       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TestGameState::onStart()
{
    u_ptr<GameObject> gameObject1 = make_unique<GameObject>();
    u_ptr<GameObject> gameObject2 = make_unique<GameObject>();
    GameObject* _gameObject2 = gameObject2.get();

    gameObject1->add_child( move(gameObject2) );
    gameObject1->is_child( _gameObject2 );
    gameObject1->remove_child( _gameObject2 );
}

void TestGameState::onUpdate()
{

}

void TestGameState::onEnd()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
