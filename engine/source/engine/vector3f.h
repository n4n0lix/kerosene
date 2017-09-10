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

class Vector3f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static const int32_t    COMPONENTS = 3;
    static const int32_t    BYTES = sizeof(float) * 3;

    static const Vector3f X_AXIS;
    static const Vector3f Y_AXIS;
    static const Vector3f Z_AXIS;

    static Vector3f zero() { return move( Vector3f(0.0f, 0.0f, 0.0f) ); }
    static Vector3f unit() { return move( Vector3f(1.0f, 1.0f, 1.0f) ); }

    static Vector3f lerp(const Vector3f source, const Vector3f target, const float amount);
    static float    angleBetween(const Vector3f vector1, const Vector3f vector2);
    static float    distanceBetween(const Vector3f vector1, const Vector3f vector2);

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Vector3f();
            explicit Vector3f(const float x, const float y);
            explicit Vector3f(const float x, const float y, const float z);
            
    bool     isUnit();
    bool     isZero();
    bool operator==(const Vector3f& o) const;
    bool operator!=(const Vector3f& o) const;

    Vector3f operator-() const;

    Vector3f operator+(const Vector3f o) const;
    Vector3f operator-(const Vector3f o) const;
    Vector3f operator*(const Vector3f o) const;
    Vector3f operator/(const Vector3f o) const;

    Vector3f& operator+=(const Vector3f o);
    Vector3f& operator-=(const Vector3f o);
    Vector3f& operator*=(const Vector3f o);
    Vector3f& operator/=(const Vector3f o);

    Vector3f operator+(const float o) const;
    Vector3f operator-(const float o) const;
    Vector3f operator*(const float o) const;
    Vector3f operator/(const float o) const;

    Vector3f& operator+=(const float o);
    Vector3f& operator-=(const float o);
    Vector3f& operator*=(const float o);
    Vector3f& operator/=(const float o);

    Vector3f normalized() const;
    float    length() const;
    float    dot(Vector3f o) const;
    Vector3f cross(Vector3f o) const;

    float x;
    float y;
    float z;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


};

ENGINE_NAMESPACE_END
