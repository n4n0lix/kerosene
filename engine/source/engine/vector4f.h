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

struct vec4 {
    float x;
    float y;
    float z;
    float w;
};

class list4f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static list4f X_AXIS;
    static list4f Y_AXIS;
    static list4f Z_AXIS;
    static list4f W_AXIS;


    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit list4f();
            explicit list4f(const float x, const float y);
            explicit list4f(const float x, const float y, const float z);
            explicit list4f(const float x, const float y, const float z, const float w);


    bool     isUnit();
    bool     isZero();
    bool operator==(const list4f& o) const;
    bool operator!=(const list4f& o) const;

    list4f operator-() const;

    list4f operator+(const list4f o) const;
    list4f operator-(const list4f o) const;
    list4f operator*(const list4f o) const;
    list4f operator/(const list4f o) const;

    list4f& operator+=(const list4f o);
    list4f& operator-=(const list4f o);
    list4f& operator*=(const list4f o);
    list4f& operator/=(const list4f o);

    list4f operator+(const float o) const;
    list4f operator-(const float o) const;
    list4f operator*(const float o) const;
    list4f operator/(const float o) const;

    list4f& operator+=(const float o);
    list4f& operator-=(const float o);
    list4f& operator*=(const float o);
    list4f& operator/=(const float o);

    list4f normalized() const;
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
