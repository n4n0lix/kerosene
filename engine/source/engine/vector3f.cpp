#include "stdafx.h"
#include "vector3f.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const Vector3f Vector3f::X_AXIS = Vector3f(1, 0, 0);
const Vector3f Vector3f::Y_AXIS = Vector3f(0, 1, 0);
const Vector3f Vector3f::Z_AXIS = Vector3f(0, 0, 1);

float Vector3f::angle_between(const Vector3f& vector1, const Vector3f& vector2)
{
    float dls = vector1.dot(vector2) / (vector1.length() * vector2.length());

    if (dls < -1.0f) {
        dls = -1.0f;
    } else if (dls > 1.0f) {
        dls = 1.0f;
    }

    return (float) std::acos(dls);
}

float Vector3f::distance_between(const Vector3f& vector1, const Vector3f& vector2)
{
    return (vector1 - vector2).length();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vector3f::Vector3f()                                                : x(0), y(0), z(0) { }
Vector3f::Vector3f(const float x, const float y)                    : x(x), y(y), z(0) { }
Vector3f::Vector3f(const float x, const float y, const float z)     : x(x), y(y), z(z) { }


bool Vector3f::is_unit()
{
    return x == 1.0f && y == 1.0f && z == 1.0f;
}

bool Vector3f::is_zero()
{
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

bool Vector3f::operator==(const Vector3f& pVector ) const
{
    return x == pVector.x
        && y == pVector.y
        && z == pVector.z;
}

bool Vector3f::operator!=(const Vector3f& pVector) const
{
    return !(*this == pVector);
}

Vector3f Vector3f::operator-() const
{
    Vector3f result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    return result;
}

Vector3f Vector3f::operator+(const Vector3f o) const
{
    Vector3f result = *this;
    result += o;
    return result;
}

Vector3f Vector3f::operator-(const Vector3f o) const
{
    Vector3f result = *this;
    result -= o;
    return result;
}

Vector3f Vector3f::operator*(const Vector3f o) const
{
    Vector3f result = *this;
    result *= o;
    return result;
}

Vector3f Vector3f::operator/(const Vector3f o) const
{
    Vector3f result = *this;
    result /= o;
    return result;
}


Vector3f& Vector3f::operator+=(const Vector3f o)
{
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f o)
{
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
}

Vector3f& Vector3f::operator*=(const Vector3f o)
{
    x *= o.x;
    y *= o.y;
    z *= o.z;
    return *this;
}

Vector3f& Vector3f::operator/=(const Vector3f o)
{
    x /= o.x;
    y /= o.y;
    z /= o.z;
    return *this;
}


Vector3f Vector3f::operator+(const float o) const
{
    Vector3f result = *this;
    result += o;
    return result;
}

Vector3f Vector3f::operator-(const float o) const
{
    Vector3f result = *this;
    result -= o;
    return result;
}

Vector3f Vector3f::operator*(const float o) const
{
    Vector3f result = *this;
    result *= o;
    return result;
}

Vector3f Vector3f::operator/(const float o) const
{
    Vector3f result = *this;
    result /= o;
    return result;
}


Vector3f& Vector3f::operator+=(const float o)
{
    x += o;
    y += o;
    z += o;
    return *this;
}

Vector3f& Vector3f::operator-=(const float o)
{
    x -= o;
    y -= o;
    z -= o;
    return *this;
}

Vector3f& Vector3f::operator*=(const float o)
{
    x *= o;
    y *= o;
    z *= o;
    return *this;
}

Vector3f& Vector3f::operator/=(const float o)
{
    x /= o;
    y /= o;
    z /= o;
    return *this;
}


Vector3f Vector3f::normalized() const
{
    Vector3f result = *this;
    float len = result.length();

    if (len != 0.0f) {
        result.x = result.x / len;
        result.y = result.y / len;
        result.z = result.z / len;
    }

    return result;
}

float Vector3f::length() const
{
    return std::sqrt(x*x + y*y + z*z);
}

float Vector3f::dot(Vector3f o) const
{
    return x * o.x + y * o.y + z * o.z;
}

Vector3f Vector3f::cross(Vector3f o) const
{
    Vector3f result = *this;
    result.x = y * o.z - z * o.y;
    result.y = z * o.x - x * o.z;
    result.z = x * o.y - y * o.x;
    return result;
}

std::ostream& operator<<( std::ostream &strm, const Vector3f &v ) {
    return strm << "( " << v.x << "f, " << v.y << "f," << v.z << "f )";
}

ENGINE_NAMESPACE_END
