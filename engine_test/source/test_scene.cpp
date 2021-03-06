#include "catch.h"

#include "scene.h"
#include "gameobject.h"

ENGINE_NAMESPACE_BEGIN

SCENARIO("gameobjects can be added and removed from the scene", "[scene]") {
    GIVEN("A scene and several gameobjects") {
        Scene       scene;
        owner<Entity>  object1 = make_owner<Entity>();
        owner<Entity>  object2 = make_owner<Entity>();
        owner<Entity>  object3 = make_owner<Entity>();

        REQUIRE(scene.get_renderers().size() == 0);

        WHEN("gameobjects are added") {
            scene.add_renderer( object1.get_non_owner() );
            scene.add_renderer( object2.get_non_owner() );
            scene.add_renderer( object3.get_non_owner() );

            THEN("they are in the scene") {
                REQUIRE( scene.get_renderers().size() == 3 );

                auto itBegin = scene.get_renderers().begin();
                auto itEnd   = scene.get_renderers().end();

                REQUIRE( std::find( itBegin, itEnd, object1.get_non_owner() ) != itEnd );
                REQUIRE( std::find( itBegin, itEnd, object2.get_non_owner() ) != itEnd );
                REQUIRE( std::find( itBegin, itEnd, object3.get_non_owner() ) != itEnd );
            }
        }

        WHEN( "the same gameobject is added multiple times" ) {
            scene.add_renderer( object1.get_non_owner() );
            scene.add_renderer( object1.get_non_owner() );
            scene.add_renderer( object1.get_non_owner() );

            THEN( "its only one time in the scene" ) {
                REQUIRE( scene.get_renderers().size() == 1 );

                auto itBegin = scene.get_renderers().begin();
                auto itEnd = scene.get_renderers().end();

                REQUIRE( std::find( itBegin, itEnd, object1.get_non_owner() ) != itEnd );
            }
        }
    }

    GIVEN( "A scene with several gameobjects" ) {
        Scene       scene;
        owner<Entity>  object1 = make_owner<Entity>();
        owner<Entity>  object2 = make_owner<Entity>();
        owner<Entity>  object3 = make_owner<Entity>();

        scene.add_renderer( object1.get_non_owner() );
        scene.add_renderer( object2.get_non_owner() );
        scene.add_renderer( object3.get_non_owner() );

        REQUIRE( scene.get_renderers().size() == 3 );

        WHEN( "gameobjects are removed" ) {
            scene.remove_renderer( object1.get_non_owner() );
            scene.remove_renderer( object2.get_non_owner() );
            scene.remove_renderer( object3.get_non_owner() );

            THEN( "they are not in the scene anymore" ) {
                REQUIRE( scene.get_renderers().size() == 0 );

                auto itBegin = scene.get_renderers().begin();
                auto itEnd = scene.get_renderers().end();

                REQUIRE( std::find( itBegin, itEnd, object1.get_non_owner() ) == itEnd );
                REQUIRE( std::find( itBegin, itEnd, object2.get_non_owner() ) == itEnd );
                REQUIRE( std::find( itBegin, itEnd, object3.get_non_owner() ) == itEnd );
            }
        }
    }
}

ENGINE_NAMESPACE_END