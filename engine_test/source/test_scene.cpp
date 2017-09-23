#include "catch.h"

#include "scene.h"
#include "gameobject.h"

ENGINE_NAMESPACE_BEGIN

SCENARIO("gameobjects can be added and removed from the scene", "[scene]") {
    GIVEN("A scene and several gameobjects") {
        Scene       scene;
        owner<GameObject>  object1 = make_owner<GameObject>();
        owner<GameObject>  object2 = make_owner<GameObject>();
        owner<GameObject>  object3 = make_owner<GameObject>();

        REQUIRE(scene.get_gameobjects().size() == 0);

        WHEN("gameobjects are added") {
            scene.add_gameobject( object1.get_non_owner() );
            scene.add_gameobject( object2.get_non_owner() );
            scene.add_gameobject( object3.get_non_owner() );

            THEN("they are in the scene") {
                REQUIRE( scene.get_gameobjects().size() == 3 );

                auto itBegin = scene.get_gameobjects().begin();
                auto itEnd   = scene.get_gameobjects().end();

                REQUIRE( std::find( itBegin, itEnd, object1.get_non_owner() ) != itEnd );
                REQUIRE( std::find( itBegin, itEnd, object2.get_non_owner() ) != itEnd );
                REQUIRE( std::find( itBegin, itEnd, object3.get_non_owner() ) != itEnd );
            }
        }

        WHEN( "the same gameobject is added multiple times" ) {
            scene.add_gameobject( object1.get_non_owner() );
            scene.add_gameobject( object1.get_non_owner() );
            scene.add_gameobject( object1.get_non_owner() );

            THEN( "its only one time in the scene" ) {
                REQUIRE( scene.get_gameobjects().size() == 1 );

                auto itBegin = scene.get_gameobjects().begin();
                auto itEnd = scene.get_gameobjects().end();

                REQUIRE( std::find( itBegin, itEnd, object1.get_non_owner() ) != itEnd );
            }
        }
    }

    GIVEN( "A scene with several gameobjects" ) {
        Scene       scene;
        owner<GameObject>  object1 = make_owner<GameObject>();
        owner<GameObject>  object2 = make_owner<GameObject>();
        owner<GameObject>  object3 = make_owner<GameObject>();

        scene.add_gameobject( object1.get_non_owner() );
        scene.add_gameobject( object2.get_non_owner() );
        scene.add_gameobject( object3.get_non_owner() );

        REQUIRE( scene.get_gameobjects().size() == 3 );

        WHEN( "gameobjects are removed" ) {
            scene.remove_gameobject( object1.get_non_owner() );
            scene.remove_gameobject( object2.get_non_owner() );
            scene.remove_gameobject( object3.get_non_owner() );

            THEN( "they are not in the scene anymore" ) {
                REQUIRE( scene.get_gameobjects().size() == 0 );

                auto itBegin = scene.get_gameobjects().begin();
                auto itEnd = scene.get_gameobjects().end();

                REQUIRE( std::find( itBegin, itEnd, object1.get_non_owner() ) == itEnd );
                REQUIRE( std::find( itBegin, itEnd, object2.get_non_owner() ) == itEnd );
                REQUIRE( std::find( itBegin, itEnd, object3.get_non_owner() ) == itEnd );
            }
        }
    }
}

ENGINE_NAMESPACE_END