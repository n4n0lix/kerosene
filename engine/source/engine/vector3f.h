#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

#define VECTOR3F_COMPONENTS 3
#define VECTOR3F_BYTES      VECTOR3F_COMPONENTS * FLOAT_BYTES

class list3f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static const int32_t    COMPONENTS = 3;
    static const int32_t    BYTES = sizeof(float) * 3;

    static const list3f X_AXIS;
    static const list3f Y_AXIS;
    static const list3f Z_AXIS;

    static list3f zero() { return move( list3f(0.0f, 0.0f, 0.0f) ); }
    static list3f unit() { return move( list3f(1.0f, 1.0f, 1.0f) ); }

    static list3f lerp(const list3f source, const list3f target, const float amount);
    static float    angleBetween(const list3f vector1, const list3f vector2);
    static float    distanceBetween(const list3f vector1, const list3f vector2);

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit list3f();
            explicit list3f(const float x, const float y);
            explicit list3f(const float x, const float y, const float z);
            
    bool     isUnit();
    bool     isZero();
    bool operator==(const list3f& o) const;
    bool operator!=(const list3f& o) const;

    list3f operator-() const;

    list3f operator+(const list3f o) const;
    list3f operator-(const list3f o) const;
    list3f operator*(const list3f o) const;
    list3f operator/(const list3f o) const;

    list3f& operator+=(const list3f o);
    list3f& operator-=(const list3f o);
    list3f& operator*=(const list3f o);
    list3f& operator/=(const list3f o);

    list3f operator+(const float o) const;
    list3f operator-(const float o) const;
    list3f operator*(const float o) const;
    list3f operator/(const float o) const;

    list3f& operator+=(const float o);
    list3f& operator-=(const float o);
    list3f& operator*=(const float o);
    list3f& operator/=(const float o);

    list3f normalized() const;
    float    length() const;
    float    dot(list3f o) const;
    list3f cross(list3f o) const;

    float x;
    float y;
    float z;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


};

ENGINE_NAMESPACE_END
