#include "stdafx.h"
#include "matrix4f.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Matrix4f Matrix4f::ZERO     = Matrix4f(0.0f);
Matrix4f Matrix4f::IDENTITY = Matrix4f(1.0f);

bool Matrix4f::is_zero( const Matrix4f& m ) {
    return m.m00 == 0.0f && m.m01 == 0.0f && m.m02 == 0.0f && m.m03 == 0.0f
        && m.m10 == 0.0f && m.m11 == 0.0f && m.m12 == 0.0f && m.m13 == 0.0f
        && m.m20 == 0.0f && m.m21 == 0.0f && m.m22 == 0.0f && m.m23 == 0.0f
        && m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f && m.m33 == 0.0f;
}

bool Matrix4f::is_identity( const Matrix4f& m ) {
    return m.m00 == 1.0f && m.m01 == 0.0f && m.m02 == 0.0f && m.m03 == 0.0f
        && m.m10 == 0.0f && m.m11 == 1.0f && m.m12 == 0.0f && m.m13 == 0.0f
        && m.m20 == 0.0f && m.m21 == 0.0f && m.m22 == 1.0f && m.m23 == 0.0f
        && m.m30 == 0.0f && m.m31 == 0.0f && m.m32 == 0.0f && m.m33 == 1.0f;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


Matrix4f::Matrix4f( float v00, float v01, float v02, float v03,
                    float v10, float v11, float v12, float v13,
                    float v20, float v21, float v22, float v23,
                    float v30, float v31, float v32, float v33 ) 
    : m00( v00 ), m01( v01 ), m02( v02 ), m03( v03 ),
      m10( v10 ), m11( v11 ), m12( v12 ), m13( v13 ),
      m20( v20 ), m21( v21 ), m22( v22 ), m23( v23 ),
      m30( v30 ), m31( v31 ), m32( v32 ), m33( v33 )
{
}

Matrix4f::Matrix4f( float diagonal )
{
    m00 = diagonal; m01 = 0.0f;     m02 = 0.0f;     m03 = 0.0f;
    m10 = 0.0f;     m11 = diagonal; m12 = 0.0f;     m13 = 0.0f;
    m20 = 0.0f;     m21 = 0.0f;     m22 = diagonal; m23 = 0.0f;
    m30 = 0.0f;     m31 = 0.0f;     m32 = 0.0f;     m33 = diagonal;
}

Matrix4f Matrix4f::rotation_axis( const float& angle, const Vector3f& axis )
{
    float c = (float)cos( angle );
    float s = (float)sin( angle );
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

    return Matrix4f( f00, f01, f02, 0,
                     f10, f11, f12, 0,
                     f20, f21, f22, 0,
                       0,   0,   0, 1 );
}

Matrix4f Matrix4f::translation( const Vector3f& v )
{
    return Matrix4f( 1, 0, 0, v.x,
                     0, 1, 0, v.y,
                     0, 0, 1, v.z,
                     0, 0, 0, 1 );
}

Matrix4f Matrix4f::scaling( const Vector3f& v )
{
    return Matrix4f( v.x,   0,   0, 0,
                       0, v.y,   0, 0,
                       0,   0, v.z, 0,
                       0,   0,   0, 1 );
}

Matrix4f Matrix4f::frustum( const float& left, const float& right, const float& bottom, const float& top, const float& znear, const float& zfar )
{
    float f00 = (2.0f * znear) / (right - left);
    float f11 = (2.0f * znear) / (top - bottom);
    float f20 = (right + left) / (right - left);
    float f21 = (top + bottom) / (top - bottom);
    float f22 = -(zfar + znear) / (zfar - znear);
    float f32 = -(2.0f * zfar * znear) / (zfar - znear);

    return Matrix4f( f00, 0, 0, 0,
        0, f11, 0, 0,
        f20, f21, f22, -1,
        0, 0, f32, 0 );
}

Matrix4f Matrix4f::perspective( const float& fov, const float& ratio, const float& znear, const float& zfar )
{
    float xmin, xmax, ymin, ymax;

    ymax = znear * (float)tan( (fov * 0.5f) * _DEG_TO_RAD );
    ymin = -ymax;

    xmin = ymin * ratio;
    xmax = ymax * ratio;

    return frustum( xmin, xmax, ymin, ymax, znear, zfar );
}

Matrix4f Matrix4f::ortho2D( const float& left, const float& right, const float& bottom, const float& top )
{
    return ortho2D( left, right, bottom, top, -1.0f, 1.0f );
}

Matrix4f Matrix4f::ortho2D( const float& left, const float& right, const float& bottom, const float& top, const float& znear, const float& zfar )
{
    if ( left == right || bottom == top ) {
        return IDENTITY;
    }

    float invZ = 1.0f / (zfar - znear);
    float invY = 1.0f / (top - bottom);
    float invX = 1.0f / (right - left);

    return Matrix4f(              2 * invX,                      0,                      0, 0,
                                         0,               2 * invY,                      0, 0,
                                         0,                      0,              -2 * invZ, 0,
                    -(right + left) * invX, -(top + bottom) * invY, -(zfar + znear) * invZ, 1 );
}

Matrix4f Matrix4f::look_at_lh( const Vector3f& eye, const Vector3f& target, const Vector3f& up )
{
    Vector3f forward = (target - eye).normalized();
    Vector3f right = up.cross( forward ).normalized();

    return Matrix4f(   right.x,   right.y,   right.z,   -right.dot( eye ),
                          up.x,      up.y,      up.z,      -up.dot( eye ),
                     forward.x, forward.y, forward.z, -forward.dot( eye ),
                             0,         0,         0,                   1);
}

Matrix4f Matrix4f::look_at_rh( const Vector3f & eye, const Vector3f & target, const Vector3f & up )
{
    Vector3f forward = (target - eye).normalized();
    Vector3f right   = up.cross( forward ).normalized();

    return Matrix4f( right.x, right.y, right.z, -right.dot( eye ),
        up.x, up.y, up.z, -up.dot( eye ),
        forward.x, forward.y, forward.z, -forward.dot( eye ),
        0, 0, 0, 1 );
}

Matrix4f::Matrix4f() : m00(0), m01(0), m02(0), m03(0),
                       m10(0), m11(0), m12(0), m13(0),
                       m20(0), m21(0), m22(0), m23(0),
                       m30(0), m31(0), m32(0), m33(0)
{
}

Matrix4f::Matrix4f(Matrix4f& copy)
{
    m00 = copy.m00;
    m01 = copy.m01;
    m02 = copy.m02;
    m03 = copy.m03;

    m10 = copy.m10;
    m11 = copy.m11;
    m12 = copy.m12;
    m13 = copy.m13;

    m20 = copy.m20;
    m21 = copy.m21;
    m22 = copy.m22;
    m23 = copy.m23;

    m30 = copy.m30;
    m31 = copy.m31;
    m32 = copy.m32;
    m33 = copy.m33;
}

bool Matrix4f::operator==(Matrix4f& o) const
{
    return m00 == o.m00 && m01 == o.m01 && m02 == o.m02 && m03 == o.m03
        && m10 == o.m10 && m11 == o.m11 && m12 == o.m12 && m13 == o.m13
        && m20 == o.m20 && m21 == o.m21 && m22 == o.m22 && m23 == o.m23
        && m30 == o.m30 && m31 == o.m31 && m32 == o.m32 && m33 == o.m33;
}

bool Matrix4f::operator!=(Matrix4f& o) const
{
    return !(*this == o);
}

Matrix4f Matrix4f::operator!() const
{
    double b0 = (m20 * m31) - (m21 * m30);
    double b1 = (m20 * m32) - (m22 * m30);
    double b2 = (m23 * m30) - (m21 * m33);
    double b3 = (m21 * m32) - (m22 * m31);
    double b4 = (m23 * m31) - (m21 * m33);
    double b5 = (m22 * m33) - (m23 * m32);

    double d11 = m11 *  b5 + m12 *  b4 + m13 * b3;
    double d12 = m10 *  b5 + m12 *  b2 + m13 * b1;
    double d13 = m10 * -b4 + m11 *  b2 + m13 * b0;
    double d14 = m10 *  b3 + m11 * -b1 + m12 * b0;

    double det = m00 * d11 - m01 * d12 + m02 * d13 - m03 * d14;
    if (abs(det) == 0.0) {
        return ZERO;
    }

    det = 1.0 / det;

    double a0 = (m00 * m11) - (m01 * m10);
    double a1 = (m00 * m12) - (m02 * m10);
    double a2 = (m03 * m10) - (m00 * m13);
    double a3 = (m01 * m12) - (m02 * m11);
    double a4 = (m03 * m11) - (m01 * m13);
    double a5 = (m02 * m13) - (m03 * m12);

    double d21 = m01 *  b5 + m02 *  b4 + m03 * b3;
    double d22 = m00 *  b5 + m02 *  b2 + m03 * b1;
    double d23 = m00 * -b4 + m01 *  b2 + m03 * b0;
    double d24 = m00 *  b3 + m01 * -b1 + m02 * b0;

    double d31 = m31 *  a5 + m32 *  a4 + m33 * a3;
    double d32 = m30 *  a5 + m32 *  a2 + m33 * a1;
    double d33 = m30 * -a4 + m31 *  a2 + m33 * a0;
    double d34 = m30 *  a3 + m31 * -a1 + m32 * a0;

    double d41 = m21 *  a5 + m22 *  a4 + m23 * a3;
    double d42 = m20 *  a5 + m22 *  a2 + m23 * a1;
    double d43 = m20 * -a4 + m21 *  a2 + m23 * a0;
    double d44 = m20 *  a3 + m21 * -a1 + m22 * a0;

    Matrix4f result;

    result.m00 = (float)(+d11 * det);
    result.m10 = (float)(-d12 * det);
    result.m20 = (float)(+d13 * det);
    result.m30 = (float)(-d14 * det);

    result.m01 = (float)(-d21 * det);
    result.m11 = (float)(+d22 * det);
    result.m21 = (float)(-d23 * det);
    result.m31 = (float)(+d24 * det);

    result.m02 = (float)(+d31 * det);
    result.m12 = (float)(-d32 * det);
    result.m22 = (float)(+d33 * det);
    result.m32 = (float)(-d34 * det);

    return result;
}

Matrix4f Matrix4f::operator-() const
{
    Matrix4f result;

    result.m00 = -m00;
    result.m01 = -m01;
    result.m02 = -m02;
    result.m03 = -m03;

    result.m10 = -m10;
    result.m11 = -m11;
    result.m12 = -m12;
    result.m13 = -m13;

    result.m20 = -m20;
    result.m21 = -m21;
    result.m22 = -m22;
    result.m23 = -m23;

    result.m30 = -m30;
    result.m31 = -m31;
    result.m32 = -m32;
    result.m33 = -m33;

    return result;
}

Matrix4f Matrix4f::operator+(Matrix4f o) const
{
    Matrix4f result;
    result.m00 = m00 + o.m00;
    result.m01 = m01 + o.m01;
    result.m02 = m02 + o.m02;
    result.m03 = m03 + o.m03;

    result.m10 = m10 + o.m10;
    result.m11 = m11 + o.m11;
    result.m12 = m12 + o.m12;
    result.m13 = m13 + o.m13;

    result.m20 = m20 + o.m20;
    result.m21 = m21 + o.m21;
    result.m22 = m22 + o.m22;
    result.m23 = m23 + o.m23;

    result.m30 = m30 + o.m30;
    result.m31 = m31 + o.m31;
    result.m32 = m32 + o.m32;
    result.m33 = m33 + o.m33;

    return result;
}

Matrix4f Matrix4f::operator-(Matrix4f o) const
{
    Matrix4f result;
    result.m00 = m00 - o.m00;
    result.m01 = m01 - o.m01;
    result.m02 = m02 - o.m02;
    result.m03 = m03 - o.m03;

    result.m10 = m10 - o.m10;
    result.m11 = m11 - o.m11;
    result.m12 = m12 - o.m12;
    result.m13 = m13 - o.m13;

    result.m20 = m20 - o.m20;
    result.m21 = m21 - o.m21;
    result.m22 = m22 - o.m22;
    result.m23 = m23 - o.m23;

    result.m30 = m30 - o.m30;
    result.m31 = m31 - o.m31;
    result.m32 = m32 - o.m32;
    result.m33 = m33 - o.m33;

    return result;
}

Matrix4f Matrix4f::operator*(Matrix4f o) const
{
    Matrix4f result;

    result.m00 = m00 * o.m00 + m10 * o.m01 + m20 * o.m02 + m30 * o.m03;
    result.m01 = m01 * o.m00 + m11 * o.m01 + m21 * o.m02 + m31 * o.m03;
    result.m02 = m02 * o.m00 + m12 * o.m01 + m22 * o.m02 + m32 * o.m03;
    result.m03 = m03 * o.m00 + m13 * o.m01 + m23 * o.m02 + m33 * o.m03;
    result.m10 = m00 * o.m10 + m10 * o.m11 + m20 * o.m12 + m30 * o.m13;
    result.m11 = m01 * o.m10 + m11 * o.m11 + m21 * o.m12 + m31 * o.m13;
    result.m12 = m02 * o.m10 + m12 * o.m11 + m22 * o.m12 + m32 * o.m13;
    result.m13 = m03 * o.m10 + m13 * o.m11 + m23 * o.m12 + m33 * o.m13;
    result.m20 = m00 * o.m20 + m10 * o.m21 + m20 * o.m22 + m30 * o.m23;
    result.m21 = m01 * o.m20 + m11 * o.m21 + m21 * o.m22 + m31 * o.m23;
    result.m22 = m02 * o.m20 + m12 * o.m21 + m22 * o.m22 + m32 * o.m23;
    result.m23 = m03 * o.m20 + m13 * o.m21 + m23 * o.m22 + m33 * o.m23;
    result.m30 = m00 * o.m30 + m10 * o.m31 + m20 * o.m32 + m30 * o.m33;
    result.m31 = m01 * o.m30 + m11 * o.m31 + m21 * o.m32 + m31 * o.m33;
    result.m32 = m02 * o.m30 + m12 * o.m31 + m22 * o.m32 + m32 * o.m33;
    result.m33 = m03 * o.m30 + m13 * o.m31 + m23 * o.m32 + m33 * o.m33;

    return result;
}

Vector4f Matrix4f::to_quaternion_4f()
{
    float x, y, z, w;

    float s;
    float tr = m00 + m11 + m22;
    if ( tr >= 0.0 ) {
        s = (float)sqrt( tr + 1.0 );
        w = s * 0.5f;
        s = 0.5f / s;
        x = (m21 - m12) * s;
        y = (m02 - m20) * s;
        z = (m10 - m01) * s;
    }
    else {
        float maximum = std::max( std::max( m00, m11 ), m22 );
        if ( maximum == m00 ) {
            s = (float)sqrt( m00 - (m11 + m22) + 1.0 );
            x = s * 0.5f;
            s = 0.5f / s;
            y = (m01 + m10) * s;
            z = (m20 + m02) * s;
            w = (m21 - m12) * s;
        }
        else if ( maximum == m11 ) {
            s = (float)sqrt( m11 - (m22 + m00) + 1.0 );
            y = s * 0.5f;
            s = 0.5f / s;
            z = (m12 + m21) * s;
            x = (m01 + m10) * s;
            w = (m02 - m20) * s;
        }
        else {
            s = (float)sqrt( m22 - (m00 + m11) + 1.0 );
            z = s * 0.5f;
            s = 0.5f / s;
            x = (m20 + m02) * s;
            y = (m12 + m21) * s;
            w = (m10 - m01) * s;
        }
    }

    return Vector4f( x, y, z, w );
}

vector<float> Matrix4f::row_major() const
{
    return { m00, m10, m20, m30,
             m01, m11, m21, m31,
             m02, m12, m22, m32,
             m03, m13, m23, m33 };
}

vector<float> Matrix4f::column_major() const
{
    return { m00, m01, m02, m03,
             m10, m11, m12, m13,
             m20, m21, m22, m23,
             m30, m31, m32, m33 };
} 

ENGINE_NAMESPACE_END