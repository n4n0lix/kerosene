#pragma once

// Std-Includes
#include <cmath>
#include <algorithm>

// Other Includes

// Internal Includes
#include "_mathdefs.h"
#include "vector2f.h"

ENGINE_NAMESPACE_BEGIN

/**
* 
*/
class Rect4f
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Rect4f from_min_max( float xMin, float yMin, float xMax, float yMax );

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

                Rect4f( Rect4f& copy);
                Rect4f( float pX, float pY, float pWidth, float pHeight);
            ~Rect4f() = default;


    bool operator==( Rect4f& o) const;
    bool operator!=( Rect4f& o) const;


    float x() const;
    void  set_x( float pX );

    float y() const;
    void  set_y( float pY );

    float width() const;
    void  set_width( float pWidth );

    float height() const;
    void  set_height( float pHeight );

    float min_x() const;
    void  set_min_x( float pMinX );

    float min_y() const;
    void  set_min_y( float pMinY );

    float max_x() const;
    void  set_max_x( float pMax );

    float max_y() const;
    void  set_max_y( float pMaxY );

    Vector2f top_left() const;
    Vector2f top_right() const;
    Vector2f bottom_left() const;
    Vector2f bottom_right() const;

private:
    float _minX, _minY, _width, _height;

    friend std::ostream& operator<<( std::ostream&, const Rect4f& );
};

ENGINE_NAMESPACE_END