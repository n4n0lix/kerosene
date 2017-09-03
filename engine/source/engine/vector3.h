#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>

// Other Includes

// Internal Includes
#include "_global.h"
#include "decimal32.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class list3
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    const int32_t    COMPONENTS = 3;
    const int32_t    BYTES = sizeof(decimal32) * 3;

    static list3 X_AXIS;
    static list3 Y_AXIS;
    static list3 Z_AXIS;

    INLINE static list3   lerp(list3 source, list3 target, decimal32 amount) {
        list3 result;
        decimal32 _1_amount = decimal32::ONE - amount;
        result.x = source.x * _1_amount + target.x * amount;
        result.y = source.y * _1_amount + target.y * amount;
        result.z = source.z * _1_amount + target.z * amount;
        return result;
    }

    INLINE static decimal32 angleBetween(list3 vector1, list3 vector2) {
        decimal32 dls = vector1.dot(vector2) / (vector1.length() * vector2.length());

        if (dls < -decimal32::ONE) {
            dls = -1.0f;
        }
        else if (dls > decimal32::ONE) {
            dls = 1.0f;
        }

        return decimal32::acos(dls);
    }

    INLINE static decimal32 distanceBetween(list3 vector1, list3 vector2) {
        return (vector1 - vector2).length();
    }

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            INLINE explicit list3()                                      : x(decimal32::fromInt(0)), y(decimal32::fromInt(0)), z(decimal32::fromInt(0)) { }
            INLINE explicit list3(decimal32 x, decimal32 y)              : x(x), y(y), z(decimal32::fromInt(0)) { }
            INLINE explicit list3(decimal32 x, decimal32 y, decimal32 z) : x(x), y(y), z(z) { }

    INLINE bool     isUnit() { return x == 1 && y == 1 && z == 1; }
    INLINE bool     isZero() { return x == 0 && y == 0 && z == 0; }

    INLINE bool operator==(list3& o) const { return x == o.x && y == o.y && z == o.z; }
    INLINE bool operator!=(list3& o) const { return !(*this == o); }

    INLINE list3 operator-() const { list3 result; result.x = -x; result.y = -y; result.z = -z; return result; }

    INLINE list3 operator+(list3 o) const { list3 result = *this; result += o; return result; }
    INLINE list3 operator-(list3 o) const { list3 result = *this; result -= o; return result; }
    INLINE list3 operator*(list3 o) const { list3 result = *this; result *= o; return result; }
    INLINE list3 operator/(list3 o) const { list3 result = *this; result /= o; return result; }

    INLINE list3& operator+=(list3 o) { x += o.x; y += o.y; z += o.z; return *this; }
    INLINE list3& operator-=(list3 o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    INLINE list3& operator*=(list3 o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
    INLINE list3& operator/=(list3 o) { x /= o.x; y /= o.y; z /= o.z; return *this; }

    INLINE list3 operator+(decimal32 o) const { list3 result = *this; result += o; return result; }
    INLINE list3 operator-(decimal32 o) const { list3 result = *this; result -= o; return result; }
    INLINE list3 operator*(decimal32 o) const { list3 result = *this; result *= o; return result; }
    INLINE list3 operator/(decimal32 o) const { list3 result = *this; result /= o; return result; }

    INLINE list3& operator+=(decimal32  o) { x += o; y += o; z += o; return *this; }
    INLINE list3& operator-=(decimal32  o) { x -= o; y -= o; z -= o; return *this; }
    INLINE list3& operator*=(decimal32  o) { x *= o; y *= o; z *= o; return *this; }
    INLINE list3& operator/=(decimal32  o) { x /= o; y /= o; z /= o; return *this; }


    INLINE list3   normalized() const
    {
        list3 result = *this;
        decimal32 len = result.length();

        if (len != decimal32::ZERO) {
            result.x = result.x / len;
            result.y = result.y / len;
            result.z = result.z / len;
        }

        return result;
    }

    INLINE decimal32 length() const {
        return decimal32::sqrt(x*x + y*y + z*z);
    }

    INLINE decimal32 dot(list3 o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    INLINE list3   cross(list3 o) const {
        list3 result = *this;
        result.x = y * o.z - z * o.y;
        result.y = z * o.x - x * o.z;
        result.z = x * o.y - y * o.x;
        return result;
    }

    decimal32  x;
    decimal32  y;
    decimal32  z;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

list3 list3::X_AXIS = list3(decimal32::ONE, decimal32::ZERO, decimal32::ZERO);
list3 list3::Y_AXIS = list3(decimal32::ZERO, decimal32::ONE, decimal32::ZERO);
list3 list3::Z_AXIS = list3(decimal32::ZERO, decimal32::ZERO, decimal32::ONE);

ENGINE_NAMESPACE_END
