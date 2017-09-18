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


    for (; !keys.empty(); keys.pop())      
    {
        KeyEvent evt = keys.front();
        if ( evt.key() == Key::ESCAPE ) {
            set_status( GameStateStatus::FINISHED );
        }

    }
}

void TestGameState::on_end()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
