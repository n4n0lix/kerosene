#pragma once
#include "stdafx.h"

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

class Vector2f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Vector2f X_AXIS;
    static Vector2f Y_AXIS;

    static float distance( Vector2f v0, Vector2f v1 );

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            Vector2f();
            Vector2f(const float x, const float y);
            ~Vector2f() = default;
            
    bool     is_unit();
    bool     is_zero();
    bool     operator==(const Vector2f& o) const;
    bool     operator!=(const Vector2f& o) const;

    Vector2f operator-() const;

    Vector2f operator+(const Vector2f o) const;
    Vector2f operator-(const Vector2f o) const;
    Vector2f operator*(const Vector2f o) const;
    Vector2f operator/(const Vector2f o) const;

    Vector2f& operator+=(const Vector2f o);
    Vector2f& operator-=(const Vector2f o);
    Vector2f& operator*=(const Vector2f o);
    Vector2f& operator/=(const Vector2f o);

    Vector2f operator+(const float o) const;
    Vector2f operator-(const float o) const;
    Vector2f operator*(const float o) const;
    Vector2f operator/(const float o) const;

    Vector2f& operator+=(const float o);
    Vector2f& operator-=(const float o);
    Vector2f& operator*=(const float o);
    Vector2f& operator/=(const float o);


    Vector2f normalized() const;
    float    length() const;
    float    cross( Vector2f& o );
    float    dot( Vector2f& o );

    float x;
    float y;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

inline float distance( Vector2f v0, Vector2f v1 ) {
    float x = v0.x - v1.x;
    float y = v0.y - v1.y;

    return std::sqrtf( x*x + y*y );
}

ENGINE_NAMESPACE_END
