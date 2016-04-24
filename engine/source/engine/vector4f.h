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

#define VECTOR4F_COMPONENTS 4
#define VECTOR4F_BYTES      VECTOR4F_COMPONENTS * FLOAT_BYTES

struct DLL_PUBLIC vec4 {
    float x;
    float y;
    float z;
    float w;
};

class DLL_PUBLIC Vector4f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Vector4f X_AXIS;
    static Vector4f Y_AXIS;
    static Vector4f Z_AXIS;
    static Vector4f W_AXIS;


    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Vector4f();
            explicit Vector4f(const float x, const float y);
            explicit Vector4f(const float x, const float y, const float z);
            explicit Vector4f(const float x, const float y, const float z, const float w);


    bool     isUnit();
    bool     isZero();
    bool operator==(const Vector4f& o) const;
    bool operator!=(const Vector4f& o) const;

    Vector4f operator-() const;

    Vector4f operator+(const Vector4f o) const;
    Vector4f operator-(const Vector4f o) const;
    Vector4f operator*(const Vector4f o) const;
    Vector4f operator/(const Vector4f o) const;

    Vector4f& operator+=(const Vector4f o);
    Vector4f& operator-=(const Vector4f o);
    Vector4f& operator*=(const Vector4f o);
    Vector4f& operator/=(const Vector4f o);

    Vector4f operator+(const float o) const;
    Vector4f operator-(const float o) const;
    Vector4f operator*(const float o) const;
    Vector4f operator/(const float o) const;

    Vector4f& operator+=(const float o);
    Vector4f& operator-=(const float o);
    Vector4f& operator*=(const float o);
    Vector4f& operator/=(const float o);

    Vector4f normalized() const;
    float    length() const;

    vec4     toVec4() const;

    float x;
    float y;
    float z;
    float w;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

ENGINE_NAMESPACE_END
