#pragma once

// Std-Includes
#include <cmath>
#include <algorithm>

// Other Includes

// Internal Includes
#include "_mathdefs.h"
#include "vector3f.h"
#include "vector4f.h"

ENGINE_NAMESPACE_BEGIN

/**
* 
*/
class Matrix4f
{
public:
    static Matrix4f ZERO;
    static Matrix4f IDENTITY;

    static bool is_zero( const Matrix4f& m );

    static bool is_identity( const Matrix4f& m );

    static Matrix4f rotation_axis( const float& angle, const Vector3f& axis );

    static Matrix4f translation( const Vector3f& v );

    static Matrix4f scaling( const Vector3f& v );

    static Matrix4f frustum( const float& left, const float& right, const float& bottom, const float& top, const float& znear, const float& zfar );

    static Matrix4f perspective( const float& fov, const float& ratio, const float& znear, const float& zfar );

    static Matrix4f ortho2D( const float& left, const float& right, const float& bottom, const float& top );

    static Matrix4f ortho2D( const float& left, const float& right, const float& bottom, const float& top, const float& znear, const float& zfar );

    static Matrix4f look_at_lh( const Vector3f& eye, const Vector3f& target, const Vector3f& up );


            Matrix4f();
            Matrix4f(Matrix4f& copy);
            Matrix4f( float v00, float v01, float v02, float v03,
                      float v10, float v11, float v12, float v13,
                      float v20, float v21, float v22, float v23,
                      float v30, float v31, float v32, float v33 );
            explicit Matrix4f(float diagonal);
            ~Matrix4f() = default;


    bool operator==(Matrix4f& o) const;
    bool operator!=(Matrix4f& o) const;

    Matrix4f operator!() const;
    Matrix4f operator-() const;

    Matrix4f operator+(Matrix4f o) const;
    Matrix4f operator-(Matrix4f o) const;
    Matrix4f operator*(Matrix4f o) const;

    Vector4f /*Quaternion4f*/ to_quaternion_4f();

    vector<float> column_major() const;
    vector<float> row_major() const;

    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;

private:

};

ENGINE_NAMESPACE_END