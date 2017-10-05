#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>
#include <ostream>
#include <exception>

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

/**
 * A fixed-point decimal implementation. (Q21.10)
 */
class decimal32
{
public:
    friend std::ostream & operator<<(std::ostream &os, const decimal32& dec) { os << dec.to_string(); return os; }

    // SIGN | INTEGRAL                 |FRACTION
    //     0|010 1010 1101 0101 0101 01|01 0111 0101
    // 1-bit| 21-bit                   |10-bit

    static const uint32 SIGN_BITS     = 1;
    static const uint32 INTEGRAL_BITS = 21;
    static const uint32 FRACTION_BITS = 10;
    
    static decimal32 INCREMENT;
    static decimal32 ZERO;
    static decimal32 ONE;

    static decimal32 _2PI;
    static decimal32 PI;
    static decimal32 PI_2;
    static decimal32 PI_4;
    static decimal32 _3PI_4;

    static decimal32 fromDouble(double d)   { return decimal32(d); }
    static double    toDouble(decimal32 d)  { return (double)d.value / (double)_ONE; }

    static decimal32 fromFloat(float d)     { return decimal32(d); }
    static float     toFloat(decimal32 d)   { return (float)d.value / (float)_ONE; }

    static decimal32 fromInt(int32_t d)     { return decimal32(d); }
    static int32     toInt(decimal32 d)     { 
        if (d.value >= 0) {
            return d.value >> FRACTION_BITS;
        }
        else {
            return -(abs(d.value) >> FRACTION_BITS);
        }
    }
    static decimal32 fromRaw(int32 value) { decimal32 result; result.value = value; return result; }

    static decimal32 sqrt(const decimal32& d);
    static decimal32 sqrt_fast(const decimal32& d);

    static decimal32 sin(const decimal32& d);
    static decimal32 cos(const decimal32& d);
    static decimal32 tan(const decimal32& d);

    static decimal32 asin(const decimal32& d);
    static decimal32 acos(const decimal32& d);
    static decimal32 atan(const decimal32& d);


            decimal32()                     { value = 0; }
            decimal32(const decimal32& d)   { value = d.value; }
            ~decimal32()                    { }
            decimal32(double o)             { value = (int32)(o * (double)_ONE); }
            decimal32(float o)              { value = (int32)(o * (float)_ONE); }
            decimal32(int o)                { value = o << FRACTION_BITS; }
            decimal32(int i, double f)      { value = (i << FRACTION_BITS) + (int32)(f * (float)_ONE); }

    bool operator!=(const decimal32& o) const { return value != o.value; };
    bool operator==(const decimal32& o) const { return value == o.value; };
    bool operator<=(const decimal32& o) const { return value <= o.value; };
    bool operator>=(const decimal32& o) const { return value >= o.value; };
    bool operator<(const decimal32& o)  const { return value < o.value; };
    bool operator>(const decimal32& o)  const { return value > o.value; };

    decimal32 operator-()                   const { decimal32 result = *this; result.value = -result.value; return result; };
    decimal32 operator+(const decimal32& o) const { decimal32 result = *this; result += o; return result; };
    decimal32 operator-(const decimal32& o) const { decimal32 result = *this; result -= o; return result; };
    decimal32 operator*(const decimal32& o) const { decimal32 result = *this; result *= o; return result; };
    decimal32 operator/(const decimal32& o) const { decimal32 result = *this; result /= o; return result; };
    decimal32 operator%(const decimal32& o) const { decimal32 result = *this; result.value = result.value % o.value; return result; };

    decimal32& operator+=(const decimal32& o) { value += o.value; return *this; };
    decimal32& operator-=(const decimal32& o) { value -= o.value; return *this; };
    decimal32& operator*=(const decimal32& o) { value = (int32)(((int64)value * (int64)o.value) >> FRACTION_BITS); return *this; };
    decimal32& operator/=(const decimal32& o) { value = (int32)(((int64)value << FRACTION_BITS) / o.value); return *this; };

    string to_string() const {
        string integralPart = std::to_string(decimal32::toInt(*this));
        string fractionalPart = std::to_string(decimal32::toDouble(*this % ONE)).substr(1);
        return integralPart.append(fractionalPart);
    }

    int32_t value;

private:
    

    static const int32      _ONE = (1 << FRACTION_BITS);
    static decimal32        ONE_PLUS_INCREMENT;
};

ENGINE_NAMESPACE_END
