#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"
#include "matrix4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class Quaternion4f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Quaternion4f X_AXIS;
    static Quaternion4f Y_AXIS;
    static Quaternion4f Z_AXIS;
    static Quaternion4f W_AXIS;

    static Quaternion4f slerp( const Quaternion4f&, const Quaternion4f&, float amount );

    static Quaternion4f rotation_axis( const Vector3f& , float );

    static Matrix4f to_rotation_mat4f( const Quaternion4f& q );

    static Quaternion4f rotationIdentity() { return std::move( Quaternion4f(0.0f, 0.0f, 0.0f, 1.0f) ); }

    static inline float dot_product( const Quaternion4f&, const Quaternion4f& );

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            Quaternion4f();
            Quaternion4f(const float x, const float y, const float z, const float w);
            ~Quaternion4f() = default;

    bool operator==(const Quaternion4f& o) const;
    bool operator!=(const Quaternion4f& o) const;

    Quaternion4f operator-() const;

    Quaternion4f operator*(const float o) const;

    Quaternion4f operator+(const Quaternion4f o) const;
    Quaternion4f operator-(const Quaternion4f o) const;
    Quaternion4f operator*(const Quaternion4f o) const;

    Quaternion4f& operator*=(const float o);

    Quaternion4f& operator+=(const Quaternion4f o);
    Quaternion4f& operator-=(const Quaternion4f o);
    Quaternion4f& operator*=(const Quaternion4f o);

    float         length() const;
    Quaternion4f  normalized() const;

    float x;
    float y;
    float z;
    float w;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

inline Quaternion4f operator*( const float& a, const Quaternion4f& b ) { return b * a; }

ENGINE_NAMESPACE_END
