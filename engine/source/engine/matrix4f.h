#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>
#include <algorithm>

// Other Includes

// Internal Includes
#include "_global.h"
#include "_mathdefs.h"
#include "vector3f.h"
#include "vector4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

/**
* A fixed-point decimal implementation. (Q21.10)
*/
class Matrix4f
{
public:
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Matrix4f ZERO;
    static Matrix4f IDENTITY;

    static bool isZero(const Matrix4f& m) {
        return m.m00 == 0.0f && m.m01 == 0.0f && m.m02 == 0.0f && m.m03 == 0.0f
            && m.m10 == 0.0f && m.m11 == 0.0f && m.m12 == 0.0f && m.m13 == 0.0f
            && m.m20 == 0.0f && m.m21 == 0.0f && m.m22 == 0.0f && m.m23 == 0.0f
            && m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f && m.m33 == 0.0f;
    }

    static bool isIdentity(const Matrix4f& m) {
        return m.m00 == 1.0f && m.m01 == 0.0f && m.m02 == 0.0f && m.m03 == 0.0f
            && m.m10 == 0.0f && m.m11 == 1.0f && m.m12 == 0.0f && m.m13 == 0.0f
            && m.m20 == 0.0f && m.m21 == 0.0f && m.m22 == 1.0f && m.m23 == 0.0f
            && m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f && m.m33 == 1.0f;
    }

    static Matrix4f rotationAxis(const float angle, const list3f axis)
    {
            float c = (float)cos(angle);
            float s = (float)sin(angle);
            float oneMinusC = 1.0f - c;
            float xy = axis.x*axis.y;
            float yz = axis.y*axis.z;
            float xz = axis.x*axis.z;
            float xs = axis.x*s;
            float ys = axis.y*s;
            float zs = axis.z*s;

            float f00 = (axis.x * axis.x * oneMinusC) + c;
            float f01 = (xy * oneMinusC) + zs;
            float f02 = (xz * oneMinusC) - ys;

            float f10 = (xy * oneMinusC) - zs;
            float f11 = (axis.y * axis.y * oneMinusC) + c;
            float f12 = (yz * oneMinusC) + xs;

            float f20 = (xz * oneMinusC) + ys;
            float f21 = (yz * oneMinusC) - xs;
            float f22 = (axis.z * axis.z * oneMinusC) + c;

            return Matrix4f(  f00,  f01,  f02, 0.0f,
                              f10,  f11,  f12, 0.0f,
                              f20,  f21,  f22, 0.0f,
                             0.0f, 0.0f, 0.0f, 0.0f);
    }

    static Matrix4f translation(list3f v)
    {
        return Matrix4f(0, 0, 0, v.x,
                        0, 0, 0, v.y,
                        0, 0, 0, v.z,
                        0, 0, 0, 0);
    }

    static Matrix4f scaling(list3f v)
    {
        return Matrix4f(v.x,   0,   0,   0,
                        0,   v.y,   0,   0,
                        0,     0, v.z,   0,
                        0,     0,   0,   0);
    }

    static Matrix4f frustum(float left, float right, float bottom, float top, float znear, float zfar) {
        float f00 = (2.0f * znear) / (right - left);
        float f11 = (2.0f * znear) / (top - bottom);
        float f20 = (right + left) / (right - left);
        float f21 = (top + bottom) / (top - bottom);
        float f22 = -(zfar + znear) / (zfar - znear);
        float f32 = -(2.0f * zfar * znear) / (zfar - znear);

        return Matrix4f(  f00,     0,     0,   0,
                            0,   f11,     0,   0,
                          f20,   f21,   f22,  -1,
                            0,     0,   f32,   0);
    }

    static Matrix4f perspective(float fov, float ratio, float znear, float zfar) {
        float xmin, xmax, ymin, ymax;

        ymax = znear * (float)tan((fov * 0.5f) * _DEG_TO_RAD);
        ymin = -ymax;

        xmin = ymin * ratio;
        xmax = ymax * ratio;

        return frustum(xmin, xmax, ymin, ymax, znear, zfar);
    }

    static Matrix4f ortho2D(float left, float right, float bottom, float top) {
        return ortho2D(left, right, bottom, top, -1.0f, 1.0f);
    }

    static Matrix4f ortho2D(float left, float right, float bottom, float top, float znear, float zfar) {
        if (left == right || bottom == top) {
            return IDENTITY;
        }

        float invZ = 1.0f / (zfar - znear);
        float invY = 1.0f / (top - bottom);
        float invX = 1.0f / (right - left);

        return Matrix4f(             2 * invX,                      0,                      0,   0,
                                            0,               2 * invY,                      0,   0,
                                            0,                      0,              -2 * invZ,   0,
                       -(right + left) * invX, -(top + bottom) * invY, -(zfar + znear) * invZ,   1);
    }

    static Matrix4f lookAtLH(list3f eye, list3f target, list3f up) {

        list3f zaxis = (target-eye).normalized();
        list3f xaxis = up.cross(zaxis).normalized();
        list3f yaxis = zaxis.cross(xaxis);

        return Matrix4f(xaxis.x, xaxis.y, xaxis.z, -xaxis.dot(eye),
                        yaxis.x, yaxis.y, yaxis.z, -yaxis.dot(eye),
                        zaxis.x, zaxis.y, zaxis.z, -zaxis.dot(eye),
                              0,       0,       0,               1);
    }

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            Matrix4f();
            Matrix4f(Matrix4f& copy);
            Matrix4f(float v00, float v01, float v02, float v03,
                     float v10, float v11, float v12, float v13,
                     float v20, float v21, float v22, float v23,
                     float v30, float v31, float v32, float v33);
            explicit Matrix4f(float diagonal);


    bool operator==(Matrix4f& o) const;
    bool operator!=(Matrix4f& o) const;

    Matrix4f operator!() const;
    Matrix4f operator-() const;

    Matrix4f operator+(Matrix4f o) const;
    Matrix4f operator-(Matrix4f o) const;
    Matrix4f operator*(Matrix4f o) const;


    list4f /*Quaternion4f*/ toQuaternion4f() {
        float x, y, z, w;

        float s;
        float tr = m00 + m11 + m22;
        if (tr >= 0.0) {
            s = (float)sqrt(tr + 1.0);
            w = s * 0.5f;
            s = 0.5f / s;
            x = (m21 - m12) * s;
            y = (m02 - m20) * s;
            z = (m10 - m01) * s;
        }
        else {
            float maximum = std::max(std::max(m00, m11), m22);
            if (maximum == m00) {
                s = (float)sqrt(m00 - (m11 + m22) + 1.0);
                x = s * 0.5f;
                s = 0.5f / s;
                y = (m01 + m10) * s;
                z = (m20 + m02) * s;
                w = (m21 - m12) * s;
            }
            else if (maximum == m11) {
                s = (float)sqrt(m11 - (m22 + m00) + 1.0);
                y = s * 0.5f;
                s = 0.5f / s;
                z = (m12 + m21) * s;
                x = (m01 + m10) * s;
                w = (m02 - m20) * s;
            }
            else {
                s = (float)sqrt(m22 - (m00 + m11) + 1.0);
                z = s * 0.5f;
                s = 0.5f / s;
                x = (m20 + m02) * s;
                y = (m12 + m21) * s;
                w = (m10 - m01) * s;
            }
        }

        return list4f(x, y, z, w);
    }

    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;

private:

};

ENGINE_NAMESPACE_END