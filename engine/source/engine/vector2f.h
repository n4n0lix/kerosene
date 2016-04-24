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

class DLL_PUBLIC Vector2f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Vector2f X_AXIS;
    static Vector2f Y_AXIS;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Vector2f();
            explicit Vector2f(const float x, const float y);
            
    bool     isUnit();
    bool     isZero();
    bool operator==(const Vector2f& o) const;
    bool operator!=(const Vector2f& o) const;

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

    float x;
    float y;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

ENGINE_NAMESPACE_END