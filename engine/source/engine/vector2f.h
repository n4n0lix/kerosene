#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <cmath>

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class list2f
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static list2f X_AXIS;
    static list2f Y_AXIS;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit list2f();
            explicit list2f(const float x, const float y);
            
    bool     isUnit();
    bool     isZero();
    bool     operator==(const list2f& o) const;
    bool     operator!=(const list2f& o) const;

    list2f operator-() const;

    list2f operator+(const list2f o) const;
    list2f operator-(const list2f o) const;
    list2f operator*(const list2f o) const;
    list2f operator/(const list2f o) const;

    list2f& operator+=(const list2f o);
    list2f& operator-=(const list2f o);
    list2f& operator*=(const list2f o);
    list2f& operator/=(const list2f o);

    list2f operator+(const float o) const;
    list2f operator-(const float o) const;
    list2f operator*(const float o) const;
    list2f operator/(const float o) const;

    list2f& operator+=(const float o);
    list2f& operator-=(const float o);
    list2f& operator*=(const float o);
    list2f& operator/=(const float o);

    list2f normalized() const;
    float    length() const;

    float x;
    float y;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

ENGINE_NAMESPACE_END
