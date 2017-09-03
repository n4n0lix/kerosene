// Header
#include "vector4f.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

list4f list4f::X_AXIS = list4f(1.0f, 0.0f, 0.0f, 0.0f);
list4f list4f::Y_AXIS = list4f(0.0f, 1.0f, 0.0f, 0.0f);
list4f list4f::Z_AXIS = list4f(0.0f, 0.0f, 1.0f, 0.0f);
list4f list4f::W_AXIS = list4f(0.0f, 0.0f, 0.0f, 1.0f);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool list4f::isUnit()
{
    return x == 1.0f && y == 1.0f && z == 1.0f && w == 1.0f;
}

bool list4f::isZero()
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

list4f::list4f()                                                            : x(0), y(0), z(0), w(0) { }
list4f::list4f(const float x, const float y)                                : x(x), y(y), z(0), w(0) { }
list4f::list4f(const float x, const float y, const float z)                 : x(x), y(y), z(z), w(0) { }
list4f::list4f(const float x, const float y, const float z, const float w)  : x(x), y(y), z(z), w(w) { }


bool list4f::operator==(const list4f& o) const
{
    return x == o.x
        && y == o.y
        && z == o.z
        && w == o.w;
}

bool list4f::operator!=(const list4f & o) const
{
    return !(*this == o);
}

list4f list4f::operator-() const
{
    list4f result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;
    return result;
}

list4f list4f::operator+(const list4f o) const
{
    list4f result = *this;
    result += o;
    return result;
}

list4f list4f::operator-(const list4f o) const
{
    list4f result = *this;
    result -= o;
    return result;
}

list4f list4f::operator*(const list4f o) const
{
    list4f result = *this;
    result *= o;
    return result;
}

list4f list4f::operator/(const list4f o) const
{
    list4f result = *this;
    result /= o;
    return result;
}


list4f& list4f::operator+=(const list4f o)
{
    x += o.x;
    y += o.y;
    z += o.z;
    w += o.w;
    return *this;
}

list4f& list4f::operator-=(const list4f o)
{
    x -= o.x;
    y -= o.y;
    z -= o.z;
    w -= o.w;
    return *this;
}

list4f& list4f::operator*=(const list4f o)
{
    x *= o.x;
    y *= o.y;
    z *= o.z;
    w *= o.w;
    return *this;
}

list4f& list4f::operator/=(const list4f o)
{
    x /= o.x;
    y /= o.y;
    z /= o.z;
    w /= o.w;
    return *this;
}


list4f list4f::operator+(const float o) const
{
    list4f result = *this;
    result += o;
    return result;
}

list4f list4f::operator-(const float o) const
{
    list4f result = *this;
    result -= o;
    return result;
}

list4f list4f::operator*(const float o) const
{
    list4f result = *this;
    result *= o;
    return result;
}

list4f list4f::operator/(const float o) const
{
    list4f result = *this;
    result /= o;
    return result;
}


list4f& list4f::operator+=(const float o)
{
    x += o;
    y += o;
    z += o;
    w += o;
    return *this;
}

list4f& list4f::operator-=(const float o)
{
    x -= o;
    y -= o;
    z -= o;    
    w -= o;
    return *this;
}

list4f& list4f::operator*=(const float o)
{
    x *= o;
    y *= o;
    z *= o;
    w *= o;
    return *this;
}

list4f& list4f::operator/=(const float o)
{
    x /= o;
    y /= o;
    z /= o;
    w /= o;
    return *this;
}

vec4 list4f::toVec4() const
{
    return { x, y, z, w };
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

