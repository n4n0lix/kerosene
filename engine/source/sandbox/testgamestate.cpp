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

void TestGameState::on_start()
{
    get_renderengine()->get_window()->set_title("kerosene - Test");

    owner<GameObject> gameObject	= make_unique<GameObject>();
	gameObject->set_rendercomponent( move( make_unique<TestRenderComponent>() ));
	add_gameobject( move(gameObject) );
}

void TestGameState::on_update()
{

}

void TestGameState::on_end()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
