#include "stdafx.h"
#include "vector2f.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vector2f Vector2f::X_AXIS = Vector2f(1.0f, 0.0f);
Vector2f Vector2f::Y_AXIS = Vector2f(0.0f, 1.0f);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vector2f::Vector2f() : x(0), y(0) {}
Vector2f::Vector2f(const float x, const float y) : x(x), y(y) {}

bool Vector2f::isUnit()
{
    return x == 1.0f && y == 1.0f;
}

bool Vector2f::isZero()
{
    return x == 0.0f && y == 0.0f;
}

bool Vector2f::operator==(const Vector2f& o) const
{
    return x == o.x
        && y == o.y;
}

bool Vector2f::operator!=(const Vector2f & o) const
{
    return !(*this == o);
}

Vector2f Vector2f::operator-() const
{
    Vector2f result;
    result.x = -x;
    result.y = -y;
    return result;
}

Vector2f Vector2f::operator+(const Vector2f o) const
{
    Vector2f result = *this;
    result += o;
    return result;
}

Vector2f Vector2f::operator-(const Vector2f o) const
{
    Vector2f result = *this;
    result -= o;
    return result;
}

Vector2f Vector2f::operator*(const Vector2f o) const
{
    Vector2f result = *this;
    result *= o;
    return result;
}

Vector2f Vector2f::operator/(const Vector2f o) const
{
    Vector2f result = *this;
    result /= o;
    return result;
}


Vector2f& Vector2f::operator+=(const Vector2f o)
{
    x += o.x;
    y += o.y;
    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f o)
{
    x -= o.x;
    y -= o.y;
    return *this;
}

Vector2f& Vector2f::operator*=(const Vector2f o)
{
    x *= o.x;
    y *= o.y;
    return *this;
}

Vector2f& Vector2f::operator/=(const Vector2f o)
{
    x /= o.x;
    y /= o.y;
    return *this;
}


Vector2f Vector2f::operator+(const float o) const
{
    Vector2f result = *this;
    result += o;
    return result;
}

Vector2f Vector2f::operator-(const float o) const
{
    Vector2f result = *this;
    result -= o;
    return result;
}

Vector2f Vector2f::operator*(const float o) const
{
    Vector2f result = *this;
    result *= o;
    return result;
}

Vector2f Vector2f::operator/(const float o) const
{
    Vector2f result = *this;
    result /= o;
    return result;
}


Vector2f& Vector2f::operator+=(const float o)
{
    x += o;
    y += o;
    return *this;
}

Vector2f& Vector2f::operator-=(const float o)
{
    x -= o;
    y -= o;
    return *this;
}

Vector2f& Vector2f::operator*=(const float o)
{
    x *= o;
    y *= o;
    return *this;
}

Vector2f& Vector2f::operator/=(const float o)
{
    x /= o;
    y /= o;
    return *this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

