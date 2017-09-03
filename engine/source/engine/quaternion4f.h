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
#include "matrix4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class Quaternion4f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Quaternion4f X_AXIS;
    static Quaternion4f Y_AXIS;
    static Quaternion4f Z_AXIS;
    static Quaternion4f W_AXIS;

    static Quaternion4f rotationAxis(list3f axis, float angle) {
            float s = (float)sin(angle / 2);

            return Quaternion4f(axis.x * s, axis.y * s, axis.z * s, (float)cos(angle / 2));
    }

    static Matrix4f toRotationMatrix4f(Quaternion4f q) {
        Matrix4f out(0.0f);

        float xx = q.x * q.x;
        float xy = q.x * q.y;
        float xz = q.x * q.z;
        float xw = q.x * q.w;

        float yy = q.y * q.y;
        float yz = q.y * q.z;
        float yw = q.y * q.w;

        float zz = q.z * q.z;
        float zw = q.z * q.w;

        out.m00 = 1.0f - 2.0f * (yy + zz);
        out.m01 = 2.0f * (xy - zw);
        out.m02 = 2.0f * (xz + yw);
        out.m03 = 0.0f;

        out.m10 = 2.0f * (xy + zw);
        out.m11 = 1.0f - 2.0f * (xx + zz);
        out.m12 = 2.0f * (yz - xw);
        out.m13 = 0.0f;

        out.m20 = 2.0f * (xz - yw);
        out.m21 = 2.0f * (yz + xw);
        out.m22 = 1.0f - 2.0f * (xx + yy);
        out.m23 = 0.0f;

        out.m30 = 0.0f;
        out.m31 = 0.0f;
        out.m32 = 0.0f;
        out.m33 = 1.0f;

        return out;
    }

    static Quaternion4f rotationIdentity() { return move( Quaternion4f(0.0f, 0.0f, 0.0f, 1.0f) ); }

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
