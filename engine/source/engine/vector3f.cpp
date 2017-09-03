// Header
#include "vector3f.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const list3f list3f::X_AXIS = list3f(1, 0, 0);
const list3f list3f::Y_AXIS = list3f(0, 1, 0);
const list3f list3f::Z_AXIS = list3f(0, 0, 1);

list3f list3f::lerp(const list3f source, const list3f target, const float amount)
{
    list3f result;
    float _1_amount = 1.0f - amount;
    result.x = source.x * _1_amount + target.x * amount;
    result.y = source.y * _1_amount + target.y * amount;
    result.z = source.z * _1_amount + target.z * amount;
    return result;
}


float list3f::angleBetween(const list3f vector1, const list3f vector2)
{
    float dls = vector1.dot(vector2) / (vector1.length() * vector2.length());

    if (dls < -1.0f) {
        dls = -1.0f;
    } else if (dls > 1.0f) {
        dls = 1.0f;
    }

    return (float) std::acos(dls);
}

float list3f::distanceBetween(const list3f vector1, const list3f vector2)
{
    return (vector1 - vector2).length();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

list3f::list3f()                                                : x(0), y(0), z(0) { }
list3f::list3f(const float x, const float y)                    : x(x), y(y), z(0) { }
list3f::list3f(const float x, const float y, const float z)     : x(x), y(y), z(z) { }


bool list3f::isUnit()
{
    return x == 1.0f && y == 1.0f && z == 1.0f;
}

bool list3f::isZero()
{
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

bool list3f::operator==(const list3f& vector) const
{
    return x == vector.x
        && y == vector.y
        && z == vector.z;
}

bool list3f::operator!=(const list3f& vector) const
{
    return !(*this == vector);
}

list3f list3f::operator-() const
{
    list3f result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    return result;
}

list3f list3f::operator+(const list3f o) const
{
    list3f result = *this;
    result += o;
    return result;
}

list3f list3f::operator-(const list3f o) const
{
    list3f result = *this;
    result -= o;
    return result;
}

list3f list3f::operator*(const list3f o) const
{
    list3f result = *this;
    result *= o;
    return result;
}

list3f list3f::operator/(const list3f o) const
{
    list3f result = *this;
    result /= o;
    return result;
}


list3f& list3f::operator+=(const list3f o)
{
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
}

list3f& list3f::operator-=(const list3f o)
{
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
}

list3f& list3f::operator*=(const list3f o)
{
    x *= o.x;
    y *= o.y;
    z *= o.z;
    return *this;
}

list3f& list3f::operator/=(const list3f o)
{
    x /= o.x;
    y /= o.y;
    z /= o.z;
    return *this;
}


list3f list3f::operator+(const float o) const
{
    list3f result = *this;
    result += o;
    return result;
}

list3f list3f::operator-(const float o) const
{
    list3f result = *this;
    result -= o;
    return result;
}

list3f list3f::operator*(const float o) const
{
    list3f result = *this;
    result *= o;
    return result;
}

list3f list3f::operator/(const float o) const
{
    list3f result = *this;
    result /= o;
    return result;
}


list3f& list3f::operator+=(const float o)
{
    x += o;
    y += o;
    z += o;
    return *this;
}

list3f& list3f::operator-=(const float o)
{
    x -= o;
    y -= o;
    z -= o;
    return *this;
}

list3f& list3f::operator*=(const float o)
{
    x *= o;
    y *= o;
    z *= o;
    return *this;
}

list3f& list3f::operator/=(const float o)
{
    x /= o;
    y /= o;
    z /= o;
    return *this;
}


list3f list3f::normalized() const
{
    list3f result = *this;
    float len = result.length();

    if (len != 0.0f) {
        result.x = result.x / len;
        result.y = result.y / len;
        result.z = result.z / len;
    }

    return result;
}

float list3f::length() const
{
    return std::sqrt(x*x + y*y + z*z);
}

float list3f::dot(list3f o) const
{
    return x * o.x + y * o.y + z * o.z;
}

list3f list3f::cross(list3f o) const
{
    list3f result = *this;
    result.x = y * o.z - z * o.y;
    result.y = z * o.x - x * o.z;
    result.z = x * o.y - y * o.x;
    return result;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
