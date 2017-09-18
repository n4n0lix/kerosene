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
	add_gameobject( std::move(gameObject) );
}

void TestGameState::on_update()
{
    queue<KeyEvent> keys = get_inputengine()->get_keyevents();

    while ( !keys.empty() ) {
        KeyEvent evt = keys.front();
        keys.pop();

        if ( evt.key() == GLFW_KEY_W ) {
            std::cout << "W pressed!\n";
        }
    }
}

void TestGameState::on_end()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
