#include "catch.h"

#include "_global.h"
#include "owner.h"

ENGINE_NAMESPACE_BEGIN

SCENARIO("weak is valid after creation from an owner", "[owner]") {
    GIVEN("an initialized owner") {
        int32* object = new int32(128);
        auto _owner = owner<int32>(object);

        REQUIRE(_owner.get() == object);

        WHEN("getting a weak") {
            auto weak = _owner.get_non_owner();

            THEN("weak is valid and both are pointing to the same, initial object") {
                REQUIRE(weak.is_valid());

                REQUIRE(_owner.get() == object);
                REQUIRE(_owner.get() == weak.get());
            }
        }
    }
}

SCENARIO("weak is invalid after its owner is destroyed", "[owner]") {
    GIVEN("an initialized owner and a corresponding weak") {
        int32* object = new int32(128);
        auto _owner = owner<int32>(object);
        auto weak  = _owner.get_non_owner();

        REQUIRE(weak.is_valid());

        WHEN("the owner ptr goes out of scope") {
            { auto __owner = std::move(_owner); }

            THEN("the weak ptr becomes invalid") {
                REQUIRE(!weak.is_valid());
            }
        }
    }
}

SCENARIO("a weak ptr points towards the same object as its owner", "[owner]") {
    GIVEN("an initialized owner") {
        int32* object = new int32(128);
        auto _owner = owner<int32>(object);

        WHEN("a weak is retrieved from the owner") {
            auto weak = _owner.get_non_owner();

            THEN("both point to the same object") {
                REQUIRE(weak.get() == _owner.get() );
            }
        }
    }
}

SCENARIO("releasing the ownership of a pointer invalidates its corresponding weaks and the owner points to null", "[owner]") {
    GIVEN("an initialized owner and a corresponding weak") {
        int32* object = new int32(128);
        auto _owner = owner<int32>(object);
        auto weak = _owner.get_non_owner();

        WHEN("the ownership is released") {
            _owner.release();

            THEN("weak becomes invalid and owner points to null") {
                REQUIRE(!weak.is_valid());
                REQUIRE(_owner.get() == nullptr);
            }
        }
    }
}

SCENARIO("owner can be compared to nullptr without method invokation or explicit conversion", "[owner]") {
    GIVEN("an initialized owner") {
        int32* object = new int32(128);
        auto _owner = owner<int32>(object);

        THEN("comparing with nullptr is false") {
            REQUIRE(_owner != nullptr);
        }
    }
}

ENGINE_NAMESPACE_END