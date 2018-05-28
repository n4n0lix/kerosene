#include "stdafx.h"
#include "rect4f.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rect4f Rect4f::from_min_max( float pXMin, float pYMin, float pXMax, float pYMax )
{
    float xMin = std::min( pXMin, pXMax );
    float xMax = std::max( pXMin, pXMax );

    float yMin = std::min( pYMin, pYMax );
    float yMax = std::max( pYMin, pYMax );

    return Rect4f( xMin, yMin, xMax - xMin, yMax - yMin );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rect4f::Rect4f( float pX, float pY, float pWidth, float pHeight )
    : _minX(0), _minY(0), _width(0), _height(0) {

    set_x( pX );
    set_y( pY );
    set_width( pWidth );
    set_height( pHeight );
}

bool Rect4f::operator==( Rect4f & o ) const
{
    return _minX == o._minX && _minY == o._minY && _width == o._width && _height == o._height;
}

float Rect4f::x() const
{
    return _minX;
}

void Rect4f::set_x( float pX )
{
    _minX = pX;
}

float Rect4f::min_x() const
{
    return _minX;
}

void Rect4f::set_min_x( float pMinX )
{
    float xDiff = _minX - pMinX;

    set_x( pMinX );
    set_width( _width - xDiff );
}

float Rect4f::y() const
{
    return _minY;
}

void Rect4f::set_y( float pY )
{
    _minY = pY;
}

float Rect4f::min_y() const
{
    return _minY;
}

void Rect4f::set_min_y( float pMinY )
{
    float yDiff = _minY - pMinY;

    set_y( pMinY );
    set_height( _height - yDiff );
}

float Rect4f::width() const
{
    return _width;
}

void Rect4f::set_width( float pWidth )
{
    _width = pWidth;

    if ( _width < 0 ) {
        _width = abs( _width );
        _minX = _minX - _width;
    }
}

float Rect4f::max_x() const
{
    return _minX + _width;
}

void Rect4f::set_max_x( float pMaxX )
{
    set_width( pMaxX - _minX );
}

float Rect4f::height() const
{
    return _height;
}

void Rect4f::set_height( float pHeight )
{
    _height = pHeight;

    if ( _height < 0 ) {
        _height = abs( _height );
        _minY = _minY - _height;
    }
}

float Rect4f::max_y() const
{
    return _minY + _height;
}

void Rect4f::set_max_y( float pMaxY )
{
    set_height( pMaxY - _minY );
}

Vector2f Rect4f::top_left() const
{
    return Vector2f( min_x(), min_y() );
}

Vector2f Rect4f::top_right() const
{
    return Vector2f( max_x(), min_y() );
}

Vector2f Rect4f::bottom_left() const
{
    return Vector2f( min_x(), max_y() );
}

Vector2f Rect4f::bottom_right() const
{
    return Vector2f( max_x(), max_y() );
}

std::ostream& operator<<( std::ostream &strm, const Rect4f &r ) {
    strm << "[ x = " << r._minX << " ,"
         << " y = " << r._minY << " ,"
         << " w = " << r._width << " ,"
         << " h = " << r._height << " ,"
         << "]\n";
    return strm;
}


ENGINE_NAMESPACE_END
