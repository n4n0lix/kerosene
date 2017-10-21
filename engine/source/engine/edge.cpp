#include "stdafx.h"
#include "edge.h"

ENGINE_NAMESPACE_BEGIN

Edge::Edge( Vector2f p0, Vector2f p1 )
    : p0(p0), p1(p1)
{}

Vector2f Edge::closes_point_to( Edge e, Vector2f v )
{
    if ( e.p1 == e.p0 ) return e.p0;

    Vector2f ab = e.p1 - e.p0;
    float t = (v - e.p0).dot( ab ) / ab.dot( ab );

    if ( t < 0 )
        t = 0.0f;
    else if ( t > 1 )
        t = 1;

    return e.p0 + (ab * t);
}

ENGINE_NAMESPACE_END


