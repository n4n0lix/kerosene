// Header
#include "quaternion4f.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


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

Quaternion4f Quaternion4f::operator+(const float o) const
{
    return Quaternion4f(x + o, y + o, z + o, w + o);
}

Quaternion4f Quaternion4f::operator-(const float o) const
{
    return Quaternion4f(x - o, y - o, z - o, w - o);
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

Quaternion4f& Quaternion4f::operator+=(const float o)
{
    x += o;
    y += o;
    z += o;
    w += o;
    return *this;
}

Quaternion4f& Quaternion4f::operator-=(const float o)
{
    x -= o;
    y -= o;
    z -= o;
    w -= o;
    return *this;
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

float Quaternion4f::length()
{
    return sqrtf(x*x + y*y + z*z + w*w);
}

Quaternion4f Quaternion4f::normalized()
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
