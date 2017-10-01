// Header
#include "quaternion4f.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Quaternion4f Quaternion4f::slerp( const Quaternion4f& pQuat0, const Quaternion4f& pQuat1, float amount )
{
    // Only unit quaternions are valid rotations.
    // Normalize to avoid undefined behavior.
    Quaternion4f q0 = pQuat0.normalized();
    Quaternion4f q1 = pQuat1.normalized();

    // Compute the cosine of the angle between the two vectors.
    double dot = dot_product( q0, q1 );

    const double DOT_THRESHOLD = 0.9995;
    if ( fabs( dot ) > DOT_THRESHOLD ) {
        // If the inputs are too close for comfort, linearly interpolate
        // and normalize the result.
        Quaternion4f result = q0 + amount * (q1 - q0);
        return result.normalized();
    }

    // If the dot product is negative, the quaternions
    // have opposite handed-ness and slerp won't take
    // the shorter path. Fix by reversing one quaternion.
    if ( dot < 0.0f ) {
        q1 = -q1;
        dot = -dot;
    }

    dot = std::min( std::max( dot, -1.0), 1.0 );    // Robustness: Stay within domain of acos()
    double theta_0 = acos( dot );  // theta_0 = angle between input vectors
    double theta = theta_0 * amount;    // theta = angle between v0 and result 

    Quaternion4f q2 = q1 - (q0 * dot);
    q2 = q2.normalized();              // { v0, v2 } is now an orthonormal basis

    return q0*cos( theta ) + q2*sin( theta );
}

Quaternion4f Quaternion4f::rotation_axis( const Vector3f& axis, float angle ) {
    float s = (float)sin( angle / 2 );

    return Quaternion4f( axis.x * s, axis.y * s, axis.z * s, (float)cos( angle / 2 ) );
}

Matrix4f Quaternion4f::to_rotation_mat4f( const Quaternion4f& q ) {
    Matrix4f out( 0.0f );

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

float Quaternion4f::dot_product( const Quaternion4f& pQuat0 , const Quaternion4f& pQuat1 )
{
    return pQuat0.x * pQuat1.x + pQuat0.y * pQuat1.y + pQuat0.z * pQuat1.z + pQuat0.w * pQuat1.w;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Quaternion4f::Quaternion4f() : x(0), y(0), z(0), w(0) { }
Quaternion4f::Quaternion4f(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) { }

bool Quaternion4f::operator==(const Quaternion4f & o) const
{
    return x == o.x && y == o.y && z == o.z && w == w;
}

bool Quaternion4f::operator!=(const Quaternion4f & o) const
{
    return !(*this == o);
}

Quaternion4f Quaternion4f::operator-() const
{
    return Quaternion4f(-x, -y, -z, w);
}

Quaternion4f Quaternion4f::operator*(const float o) const
{
    return Quaternion4f(x * o, y * o, z * o, w * o);
}

Quaternion4f Quaternion4f::operator+(const Quaternion4f o) const
{
    Quaternion4f result = *this;
    result += o;
    return result;
}

Quaternion4f Quaternion4f::operator-(const Quaternion4f o) const
{
    Quaternion4f result = *this;
    result -= o;
    return result;
}

Quaternion4f Quaternion4f::operator*(const Quaternion4f o) const
{
    Quaternion4f result = *this;
    result *= o;
    return result;
}

Quaternion4f& Quaternion4f::operator*=(const float o)
{
    x = x * o;
    y = y * o;
    z = z * o;
    w = w * o;

    return *this;
}

Quaternion4f& Quaternion4f::operator+=(const Quaternion4f o)
{
    x += o.x;
    y += o.y;
    z += o.z;
    w += o.w;
    return *this;
}

Quaternion4f& Quaternion4f::operator-=(const Quaternion4f o)
{
    x -= o.x;
    y -= o.y;
    z -= o.z;
    w -= o.w;
    return *this;
}

Quaternion4f& Quaternion4f::operator*=(const Quaternion4f o)
{
    float _x = x;
    float _y = y;
    float _z = z;
    float _w = w;

    x =  _x * o.w + _y * o.z - _z * o.y + _w * o.x;
    y = -_x * o.z + _y * o.w + _z * o.x + _w * o.y;
    z =  _x * o.y - _y * o.x + _z * o.w + _w * o.z;
    w = -_x * o.x - _y * o.y - _z * o.z + _w * o.w;

    return *this;
}

float Quaternion4f::length() const
{
    return sqrtf(x*x + y*y + z*z + w*w);
}

Quaternion4f Quaternion4f::normalized() const
{
    float length = this->length();
    if (length == 0.0f)
    {
        return *this;
    }

    float inverse = 1.0f / length;
    return Quaternion4f(x*inverse, y*inverse, z*inverse, w*inverse);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
