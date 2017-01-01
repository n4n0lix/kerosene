#pragma once

#include "test.h"

#include "_global.h"
#include "vector3f.h"
    using kerosene::Vector3f;

BEHAVIOUR(Vector3f, if_all_members_are_zero_then_isUnit_must_return_true)
    Vector3f subject(1.0f, 1.0f, 1.0f);

    IS_TRUE( subject.isUnit() )
END

BEHAVIOUR(Vector3f, if_atleast_one_member_is_not_zero_then_isUnit_must_return_false)
    Vector3f subject(0.0f, 0.0f, 0.1f);

    IS_FALSE( subject.isUnit() )
END
