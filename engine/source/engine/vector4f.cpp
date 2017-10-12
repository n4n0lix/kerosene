#include "stdafx.h"
#include "vector4f.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vector4f Vector4f::X_AXIS = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
Vector4f Vector4f::Y_AXIS = Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
Vector4f Vector4f::Z_AXIS = Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
Vector4f Vector4f::W_AXIS = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool Vector4f::isUnit()
{
    return x == 1.0f && y == 1.0f && z == 1.0f && w == 1.0f;
}

bool Vector4f::isZero()
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

Vector4f::Vector4f()                                                            : x(0), y(0), z(0), w(0) { }
Vector4f::Vector4f(const float x, const float y)                                : x(x), y(y), z(0), w(0) { }
Vector4f::Vector4f(const float x, const float y, const float z)                 : x(x), y(y), z(z), w(0) { }
Vector4f::Vector4f(const float x, const float y, const float z, const float w)  : x(x), y(y), z(z), w(w) { }


bool Vector4f::operator==(const Vector4f& o) const
{
    return x == o.x
        && y == o.y
        && z == o.z
        && w == o.w;
}

bool Vector4f::operator!=(const Vector4f & o) const
{
    return !(*this == o);
}

Vector4f Vector4f::operator-() const
{
    Vector4f result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;
    return result;
}

Vector4f Vector4f::operator+(const Vector4f o) const
{
    Vector4f result = *this;
    result += o;
    return result;
}

Vector4f Vector4f::operator-(const Vector4f o) const
{
    Vector4f result = *this;
    result -= o;
    return result;
}

Vector4f Vector4f::operator*(const Vector4f o) const
{
    Vector4f result = *this;
    result *= o;
    return result;
}

Vector4f Vector4f::operator/(const Vector4f o) const
{
    Vector4f result = *this;
    result /= o;
    return result;
}


Vector4f& Vector4f::operator+=(const Vector4f o)
{
    x += o.x;
    y += o.y;
    z += o.z;
    w += o.w;
    return *this;
}

Vector4f& Vector4f::operator-=(const Vector4f o)
{
    x -= o.x;
    y -= o.y;
    z -= o.z;
    w -= o.w;
    return *this;
}

Vector4f& Vector4f::operator*=(const Vector4f o)
{
    x *= o.x;
    y *= o.y;
    z *= o.z;
    w *= o.w;
    return *this;
}

Vector4f& Vector4f::operator/=(const Vector4f o)
{
    x /= o.x;
    y /= o.y;
    z /= o.z;
    w /= o.w;
    return *this;
}


Vector4f Vector4f::operator+(const float o) const
{
    Vector4f result = *this;
    result += o;
    return result;
}

Vector4f Vector4f::operator-(const float o) const
{
    Vector4f result = *this;
    result -= o;
    return result;
}

Vector4f Vector4f::operator*(const float o) const
{
    Vector4f result = *this;
    result *= o;
    return result;
}

Vector4f Vector4f::operator/(const float o) const
{
    Vector4f result = *this;
    result /= o;
    return result;
}


Vector4f& Vector4f::operator+=(const float o)
{
    x += o;
    y += o;
    z += o;
    w += o;
    return *this;
}

Vector4f& Vector4f::operator-=(const float o)
{
    x -= o;
    y -= o;
    z -= o;    
    w -= o;
    return *this;
}

Vector4f& Vector4f::operator*=(const float o)
{
    x *= o;
    y *= o;
    z *= o;
    w *= o;
    return *this;
}

Vector4f& Vector4f::operator/=(const float o)
{
    x /= o;
    y /= o;
    z /= o;
    w /= o;
    return *this;
}

vec4 Vector4f::toVec4() const
{
    return { x, y, z, w };
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

