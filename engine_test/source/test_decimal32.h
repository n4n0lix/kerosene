#pragma once

#include <math.h>

#include "decimal32.h"
        using kerosene::decimal32;

//
// BEHAVIOUR
//

BEHAVIOUR(from_int_0_must_convert_back_to_int_0)
{
    IS_TRUE(decimal32::toInt(decimal32(0)) == 0)
    PASS
}

BEHAVIOUR(from_float_0_must_convert_back_to_float_0)
{
    IS_TRUE(decimal32::toFloat(decimal32(0.0f)) == 0.0)
    PASS
}

BEHAVIOUR(from_double_0_must_convert_back_to_double_0)
{
    IS_TRUE(decimal32::toDouble(decimal32(0.0)) == 0.0)
    PASS
}

BEHAVIOUR(operator_unequeal)
{
    IS_TRUE(decimal32( 0.0) != decimal32( 1.0))
    IS_TRUE(decimal32( 1.0) != decimal32( 0.0))
    IS_TRUE(decimal32(-1.0) != decimal32( 0.0))
    IS_TRUE(decimal32( 0.0) != decimal32(-1.0))

    IS_FALSE(decimal32( 1.0) != decimal32( 1.0))
    IS_FALSE(decimal32( 0.0) != decimal32( 0.0))
    IS_FALSE(decimal32(-1.0) != decimal32(-1.0))
    PASS
}

BEHAVIOUR(operator_equeal)
{
    IS_FALSE(decimal32( 0.0) == decimal32( 1.0))
    IS_FALSE(decimal32( 1.0) == decimal32( 0.0))
    IS_FALSE(decimal32(-1.0) == decimal32( 0.0))
    IS_FALSE(decimal32( 0.0) == decimal32(-1.0))

    IS_TRUE(decimal32( 1.0) == decimal32( 1.0))
    IS_TRUE(decimal32( 0.0) == decimal32( 0.0))
    IS_TRUE(decimal32(-1.0) == decimal32(-1.0))
    PASS
}

BEHAVIOUR(operator_less_equeal)
{
    IS_TRUE(decimal32(-1.0) <= decimal32(0.0))
    IS_TRUE(decimal32(-1.0) <= decimal32(1.0))
    IS_TRUE(decimal32( 0.0) <= decimal32(1.0))

    IS_TRUE(decimal32(0.0) <= decimal32(0.0))

    IS_FALSE(decimal32(1.0) <= decimal32( 0.0))
    IS_FALSE(decimal32(0.0) <= decimal32(-1.0))
    PASS
}

BEHAVIOUR(operator_plus)
{

    // (+, +) -> +
    //                  Expected                Result                                     Delta
    IS_EQUALD( decimal32(6,.0),         decimal32(2,.8) + decimal32(3,.2),              decimal32::INCREMENT)
    IS_EQUALD( decimal32(2),            decimal32(0)    + decimal32(2),                 decimal32::INCREMENT)
    IS_EQUALD( decimal32(120000,.277),  decimal32(61234,.512) + decimal32(58765,.765),  decimal32::INCREMENT)

    // (-, +) -> +
    IS_EQUALS(decimal32(-2) + decimal32(3), decimal32(1))

    // (-, +) -> -
    IS_EQUALS(decimal32(-5) + decimal32(3), decimal32(-2))

    // (-, -) -> -
    IS_EQUALS(decimal32(-3) + decimal32(-2), decimal32(-5))

    PASS
}

//
// PERFORMANCE
//

PERFORMANCE(sqrt,       5000000) { decimal32::sqrt(decimal32::fromRaw(abs(rand()))); }
PERFORMANCE(sqrt_fast,  5000000) { decimal32::sqrt_fast(decimal32::fromRaw(abs(rand()))); }
PERFORMANCE(sin,        5000000) { decimal32::sin(decimal32::fromRaw(rand())); }
PERFORMANCE(cos,        5000000) { decimal32::cos(decimal32::fromRaw(rand())); }
PERFORMANCE(tan,        5000000) { decimal32::tan(decimal32::fromRaw(rand())); }
PERFORMANCE(asin,       5000000) { decimal32::asin(decimal32::fromRaw(rand())); }
PERFORMANCE(acos,       5000000) { decimal32::acos(decimal32::fromRaw(rand())); }
PERFORMANCE(atan,       5000000) { decimal32::atan(decimal32::fromRaw(rand())); }