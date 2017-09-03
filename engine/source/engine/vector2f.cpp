// Header
#include "vector2f.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

list2f list2f::X_AXIS = list2f(1.0f, 0.0f);
list2f list2f::Y_AXIS = list2f(0.0f, 1.0f);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

list2f::list2f() : x(0), y(0) {}
list2f::list2f(const float x, const float y) : x(x), y(y) {}

bool list2f::isUnit()
{
    return x == 1.0f && y == 1.0f;
}

bool list2f::isZero()
{
    return x == 0.0f && y == 0.0f;
}

bool list2f::operator==(const list2f& o) const
{
    return x == o.x
        && y == o.y;
}

bool list2f::operator!=(const list2f & o) const
{
    return !(*this == o);
}

list2f list2f::operator-() const
{
    list2f result;
    result.x = -x;
    result.y = -y;
    return result;
}

list2f list2f::operator+(const list2f o) const
{
    list2f result = *this;
    result += o;
    return result;
}

list2f list2f::operator-(const list2f o) const
{
    list2f result = *this;
    result -= o;
    return result;
}

list2f list2f::operator*(const list2f o) const
{
    list2f result = *this;
    result *= o;
    return result;
}

list2f list2f::operator/(const list2f o) const
{
    list2f result = *this;
    result /= o;
    return result;
}


list2f& list2f::operator+=(const list2f o)
{
    x += o.x;
    y += o.y;
    return *this;
}

list2f& list2f::operator-=(const list2f o)
{
    x -= o.x;
    y -= o.y;
    return *this;
}

list2f& list2f::operator*=(const list2f o)
{
    x *= o.x;
    y *= o.y;
    return *this;
}

list2f& list2f::operator/=(const list2f o)
{
    x /= o.x;
    y /= o.y;
    return *this;
}


list2f list2f::operator+(const float o) const
{
    list2f result = *this;
    result += o;
    return result;
}

list2f list2f::operator-(const float o) const
{
    list2f result = *this;
    result -= o;
    return result;
}

list2f list2f::operator*(const float o) const
{
    list2f result = *this;
    result *= o;
    return result;
}

list2f list2f::operator/(const float o) const
{
    list2f result = *this;
    result /= o;
    return result;
}


list2f& list2f::operator+=(const float o)
{
    x += o;
    y += o;
    return *this;
}

list2f& list2f::operator-=(const float o)
{
    x -= o;
    y -= o;
    return *this;
}

list2f& list2f::operator*=(const float o)
{
    x *= o;
    y *= o;
    return *this;
}

list2f& list2f::operator/=(const float o)
{
    x /= o;
    y /= o;
    return *this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

