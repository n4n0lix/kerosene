// Header
#include "vector3.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vector3 Vector3::X_AXIS = Vector3(decimal32::ONE,  decimal32::ZERO, decimal32::ZERO);
Vector3 Vector3::Y_AXIS = Vector3(decimal32::ZERO, decimal32::ONE,  decimal32::ZERO);
Vector3 Vector3::Z_AXIS = Vector3(decimal32::ZERO, decimal32::ZERO, decimal32::ONE);

Vector3 Vector3::lerp(Vector3 source, Vector3 target, decimal32 amount)
{
    Vector3 result;
    decimal32 _1_amount = decimal32::ONE - amount;
    result.x = source.x * _1_amount + target.x * amount;
    result.y = source.y * _1_amount + target.y * amount;
    result.z = source.z * _1_amount + target.z * amount;
    return result;
}


//float Vector3::angleBetween(Vector3 vector1, Vector3 vector2)
//{
//    decimal32 dls = vector1.dot(vector2) / (vector1.length() * vector2.length());

//    if (dls < -decimal32::ONE) {
//        dls = -1.0f;
//    } else if (dls > decimal32::ONE) {
//        dls = 1.0f;
//    }

//    return (float) decimal32::acos(dls);
//}

//float Vector3::distanceBetween(Vector3 vector1, Vector3 vector2)
//{
//    return (vector1 - vector2).length();
//}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vector3::Vector3() : x(decimal32::fromInt(0)), y(decimal32::fromInt(0)), z(decimal32::fromInt(0)) { }
Vector3::Vector3(decimal32 x, decimal32 y)              : x(x), y(y), z(decimal32::fromInt(0)) { }
Vector3::Vector3(decimal32 x, decimal32 y, decimal32 z) : x(x), y(y), z(z) { }

bool Vector3::operator==(Vector3& vector) const 
{
    return x == vector.x
        && y == vector.y
        && z == vector.z;
}

bool Vector3::operator!=(Vector3& vector) const
{
    return !(*this == vector);
}

Vector3 Vector3::operator-() const
{
    Vector3 result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    return result;
}

Vector3 Vector3::operator+(Vector3 o) const
{
    Vector3 result = *this;
    result += o;
    return result;
}

Vector3 Vector3::operator-(Vector3 o) const
{
    Vector3 result = *this;
    result -= o;
    return result;
}

Vector3 Vector3::operator*(Vector3 o) const
{
    Vector3 result = *this;
    result *= o;
    return result;
}

Vector3 Vector3::operator/(Vector3 o) const
{
    Vector3 result = *this;
    result /= o;
    return result;
}


Vector3& Vector3::operator+=(Vector3 o)
{
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
}

Vector3& Vector3::operator-=(Vector3 o)
{
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
}

Vector3& Vector3::operator*=(Vector3 o)
{
    x *= o.x;
    y *= o.y;
    z *= o.z;
    return *this;
}

Vector3& Vector3::operator/=(Vector3 o)
{
    x /= o.x;
    y /= o.y;
    z /= o.z;
    return *this;
}


Vector3 Vector3::operator+(decimal32 o) const
{
    Vector3 result = *this;
    result += o;
    return result;
}

Vector3 Vector3::operator-(decimal32 o) const
{
    Vector3 result = *this;
    result -= o;
    return result;
}

Vector3 Vector3::operator*(decimal32 o) const
{
    Vector3 result = *this;
    result *= o;
    return result;
}

Vector3 Vector3::operator/(decimal32 o) const
{
    Vector3 result = *this;
    result /= o;
    return result;
}


Vector3& Vector3::operator+=(decimal32 o)
{
    x += o;
    y += o;
    z += o;
    return *this;
}

Vector3& Vector3::operator-=(decimal32 o)
{
    x -= o;
    y -= o;
    z -= o;
    return *this;
}

Vector3& Vector3::operator*=(decimal32 o)
{
    x *= o;
    y *= o;
    z *= o;
    return *this;
}

Vector3& Vector3::operator/=(decimal32 o)
{
    x /= o;
    y /= o;
    z /= o;
    return *this;
}


Vector3 Vector3::normalized() const
{
    Vector3 result = *this;
    decimal32 len = result.length();

    if (len != decimal32::ZERO) {
        result.x = result.x / len;
        result.y = result.y / len;
        result.z = result.z / len;
    }

    return result;
}

decimal32 Vector3::length() const
{
    return decimal32::sqrt(x*x + y*y + z*z);
}

decimal32 Vector3::dot(Vector3 o) const
{
    return x * o.x + y * o.y + z * o.z;
}

Vector3 Vector3::cross(Vector3 o) const
{
    Vector3 result = *this;
    result.x = y * o.z - z * o.y;
    result.y = z * o.x - x * o.z;
    result.z = x * o.y - y * o.x;
    return result;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
