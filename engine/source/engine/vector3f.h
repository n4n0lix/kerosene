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

    static Vector3f zero() { return std::move( Vector3f(0.0f, 0.0f, 0.0f) ); }
    static Vector3f unit() { return std::move( Vector3f(1.0f, 1.0f, 1.0f) ); }

    static inline Vector3f lerp( const Vector3f& source, const Vector3f& target, const float& amount )
    {
        Vector3f result;
        float _1_amount = 1.0f - amount;
        result.x = source.x * _1_amount + target.x * amount;
        result.y = source.y * _1_amount + target.y * amount;
        result.z = source.z * _1_amount + target.z * amount;
        return result;
    }

    static float    angle_between(const Vector3f& vector1, const Vector3f& vector2 );
    static float    distance_between(const Vector3f& vector1, const Vector3f& vector2 );

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            Vector3f();
            Vector3f(const float x, const float y);
            Vector3f(const float x, const float y, const float z);
            ~Vector3f() = default;

    bool     is_unit();
    bool     is_zero();
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

    friend std::ostream& operator<<( std::ostream&, const Vector3f& );
};

ENGINE_NAMESPACE_END
