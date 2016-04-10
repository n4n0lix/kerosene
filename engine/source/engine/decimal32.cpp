// Header
#include "decimal32.h"
ENGINE_NAMESPACE_BEGIN

// Public static
decimal32 decimal32::INCREMENT = decimal32::fromRaw(1);
decimal32 decimal32::ZERO = decimal32(0);
decimal32 decimal32::ONE = decimal32(1);
decimal32 decimal32::PI = decimal32(3.141592653589793238462643383279);
decimal32 decimal32::_2PI = decimal32::PI * decimal32(2);
decimal32 decimal32::PI_2 = decimal32::PI / decimal32(2);
decimal32 decimal32::PI_4 = decimal32::PI / decimal32(4);
decimal32 decimal32::_3PI_4 = (decimal32(3) * decimal32::PI) / decimal32(4);

// Private static
decimal32 decimal32::ONE_PLUS_INCREMENT = ONE + decimal32::fromRaw(1);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

decimal32 decimal32::sqrt(const decimal32& d)
{
    if (d <= ZERO) {
        if (d == ZERO) {
            return ZERO;
        }
        throw new EngineException("The square root of a negative number is undefined!");
    }

    // Binary search
    //qDebug() << "sqrt(" << decimal32::toDouble(d) << ")";

    decimal32 temp;
    decimal32 x;
    decimal32 x2;

    // Skip first bit (sign bit)
    for(int32_t counter = 16; counter >= 0; counter--) {
        temp.value = x.value; // If x*x becomes larger than d, we need to deactivate the last activated bit
        x.value |= 1 << counter;
        x2 = x*x;

        if(x2 > d) {
            x.value = temp.value;
        } else if (x2 == d) {
            return x;
        }
    }
    return x;
}

decimal32 decimal32::sqrt_fast(const decimal32& d)
{
    if (d <= ZERO) {
        if (d == ZERO) {
            return ZERO;
        }
        throw new EngineException("The square root of a negative number is undefined!");
    }

    return decimal32::fromDouble(std::sqrt(decimal32::toDouble(d)));
}

decimal32 decimal32::sin(const decimal32& d)
{
    // 1# Map the value to the range [-2PI, 2PI]
    decimal32 dec = d;
    dec =  dec % _2PI;

    // 2# Convert double for higher precision
    double value = decimal32::toDouble(dec);

    // 3# Calc sine
    double sine = std::sin(value);

    // 4# Return result
    return decimal32::fromDouble(sine);
}

decimal32 decimal32::cos(const decimal32& d)
{
    // 1# Map the value to the range [-2PI, 2PI]
    decimal32 dec = d;
    dec =  dec % _2PI;

    // 2# Convert double for higher precision
    double value = decimal32::toDouble(dec);

    // 3# Calc cosine
    double cosine = std::cos(value);

    // 4# Return result
    return decimal32::fromDouble(cosine);
}

decimal32 decimal32::tan(const decimal32& d)
{
    // 1# Map the value to the range [-2PI, 2PI]
    decimal32 dec = d;
    dec =  dec % _2PI;

    // 2# Convert double for higher precision
    double value = decimal32::toDouble(dec);

    // 3# Calc sine
    double tan = std::tan(value);

    // 4# Return result
    return decimal32::fromDouble(tan);
}

decimal32 decimal32::asin(const decimal32& d)
{
    // 1# Map the value to the range [-1, 1]
    decimal32 dec = d;
    dec =  dec % ONE_PLUS_INCREMENT;

    // 2# Convert double for higher precision
    double value = decimal32::toDouble(dec);

    // 3# Calc arcsine
    double arcsine = std::asin(value);

    // 4# Return result
    return decimal32::fromDouble(arcsine);
}

decimal32 decimal32::acos(const decimal32& d)
{
    // 1# Map the value to the range [-1, 1]
    decimal32 dec = d;
    dec =  dec % ONE_PLUS_INCREMENT;

    // 2# Convert double for higher precision
    double value = decimal32::toDouble(dec);

    // 3# Calc arccosine
    double arccosine = std::acos(value);

    // 4# Return result
    return decimal32::fromDouble(arccosine);
}

decimal32 decimal32::atan(const decimal32& d)
{
    // 1# Convert double for higher precision
    double value = decimal32::toDouble(d);

    // 2# Calc arctan
    double arctan = std::atan(value);

    // 3# Return result
    return decimal32::fromDouble(arctan);
}

ENGINE_NAMESPACE_END
