#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DLL_PUBLIC Quaternion4f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Quaternion4f X_AXIS;
    static Quaternion4f Y_AXIS;
    static Quaternion4f Z_AXIS;
    static Quaternion4f W_AXIS;

    static Quaternion4f rotationAxis(Vector3f axis, float angle) {
            float s = (float)sin(angle / 2);

            return Quaternion4f(axis.x * s, axis.y * s, axis.z * s, (float)cos(angle / 2));
    }

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Quaternion4f();
            explicit Quaternion4f(const float x, const float y, const float z, const float w);

    bool operator==(const Quaternion4f& o) const;
    bool operator!=(const Quaternion4f& o) const;

    Quaternion4f operator-() const;

    Quaternion4f operator+(const float o) const;
    Quaternion4f operator-(const float o) const;
    Quaternion4f operator*(const float o) const;

    Quaternion4f operator+(const Quaternion4f o) const;
    Quaternion4f operator-(const Quaternion4f o) const;
    Quaternion4f operator*(const Quaternion4f o) const;

    Quaternion4f& operator+=(const float o);
    Quaternion4f& operator-=(const float o);
    Quaternion4f& operator*=(const float o);

    Quaternion4f& operator+=(const Quaternion4f o);
    Quaternion4f& operator-=(const Quaternion4f o);
    Quaternion4f& operator*=(const Quaternion4f o);

    float         length();
    Quaternion4f  normalized();

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
