// Header
#include "testgamestate.h"

using namespace ENGINE_NAMESPACE;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Protected                       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TestGameState::on_start()
{
    get_renderengine()->get_window()->set_title("kerosene - Test");

    owner<GameObject> gameObject = make_owner<GameObject>();
	gameObject->set_rendercomponent( std::move( make_owner<TestRenderComponent>() ));
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
