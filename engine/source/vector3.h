#ifndef VECTOR3_H
#define VECTOR3_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>

// Other Includes

// Internal Includes
#include "_global.h"
#include "decimal32.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DLL_PUBLIC Vector3
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    const int32_t    COMPONENTS = 3;
    const int32_t    BYTES = sizeof(decimal32) * 3;

    static Vector3 X_AXIS;
    static Vector3 Y_AXIS;
    static Vector3 Z_AXIS;

    static bool     isUnit(Vector3 vector);
    static bool     isZero(Vector3 vector);

    static Vector3  lerp(Vector3 source, Vector3 target, decimal32 amount);
    static float    angleBetween(Vector3 vector1, Vector3 vector2);
    static float    distanceBetween(Vector3 vector1, Vector3 vector2);

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Vector3();
            explicit Vector3(decimal32 x, decimal32 y);
            explicit Vector3(decimal32 x, decimal32 y, decimal32 z);

    bool operator==(Vector3& o) const;
    bool operator!=(Vector3& o) const;

    Vector3 operator-() const;

    Vector3 operator+(Vector3 o) const;
    Vector3 operator-(Vector3 o) const;
    Vector3 operator*(Vector3 o) const;
    Vector3 operator/(Vector3 o) const;

    Vector3& operator+=(Vector3 o);
    Vector3& operator-=(Vector3 o);
    Vector3& operator*=(Vector3 o);
    Vector3& operator/=(Vector3 o);

    Vector3 operator+(decimal32 o) const;
    Vector3 operator-(decimal32  o) const;
    Vector3 operator*(decimal32  o) const;
    Vector3 operator/(decimal32  o) const;

    Vector3& operator+=(decimal32  o);
    Vector3& operator-=(decimal32  o);
    Vector3& operator*=(decimal32  o);
    Vector3& operator/=(decimal32  o);

    Vector3   normalized() const;
    decimal32 length() const;
    decimal32 dot(Vector3 o) const;
    Vector3   cross(Vector3 o) const;

    decimal32  x;
    decimal32  y;
    decimal32  z;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


};

ENGINE_NAMESPACE_END
#endif // VECTOR3_H
