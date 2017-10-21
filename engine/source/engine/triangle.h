#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "value.h"
#include "vector2f.h"
#include "edge.h"

ENGINE_NAMESPACE_BEGIN

struct ClosestEdgeResult {
    Edge  closestEdge;
    float distance;
};

struct Triangle : public Value {

    Triangle( Vector2f p0, Vector2f p1, Vector2f p2 );

    // TODO: Implement == / != operators

    Vector2f p0;
    Vector2f p1;
    Vector2f p2;

    float min_x();
    float min_y();
    float max_x();
    float max_y();

    bool is_ccw();
    bool contains( Vector2f pr );
    bool has_vertex( Vector2f pr );

    bool is_neighbour_to( Edge e );
    bool is_point_in_circumcircle( Vector2f p );
    ClosestEdgeResult get_closest_edge_to( Vector2f );
    Vector2f get_opposing_point( Edge e );

    Vector2f circumcenter();

};

Triangle::Triangle( Vector2f p0, Vector2f p1, Vector2f p2 ) 
    : p0(p0), p1(p1), p2(p2)
{}

inline float Triangle::min_x() { return std::min( p0.x, p1.x, p2.x ); }
inline float Triangle::min_y() { return std::min( p0.y, p1.y, p2.y ); }
inline float Triangle::max_x() { return std::max( p0.x, p1.x, p2.x ); }
inline float Triangle::max_y() { return std::max( p0.y, p1.y, p2.y ); }

// Real-Time Collision Detection
// Christer Ericson, CRC Press, 2004.
// ISBN 1558607323, chap. 5, p. 206.
bool Triangle::contains( Vector2f pr )
{
    float pab = (pr - p0).cross( p1 - p0 );
    float pbc = (pr - p1).cross( p2 - p1 );
    if ( std::signbit( pab ) != std::signbit( pbc ) ) return false;

    float pca = (pr - p2).cross( p0 - p2 );
    if ( std::signbit( pab) != std::signbit( pca ) ) return false;

    return true;
}

// Art Gallery Theorems and Algorithms
// Joseph O'Rourke, Oxford University Press 1987,
// ISBN 0-19-503965-3, p. 201. 
// Simplified by Jim Ward.
Vector2f Triangle::circumcenter()
{
    float x02_ = p0.x - p2.x;
    float x12_ = p1.x - p2.x;
    float x02 = p0.x + p2.x;
    float x12 = p1.x + p2.x;

    float y02_ = p0.y - p2.y;
    float y12_ = p1.y - p2.y;
    float y02 = p0.y + p2.y;
    float y12 = p1.y + p2.y;

    float D = x02_ * y12_ - x12_ * y02_;
    float cx = ((x02_ * x02 + y02_ * y02) / 2 * y12_ - (x12_ * x12 + y12_ * y12) / 2 * y02_) / D;
    float cy = ((x12_ * x12 + y12_ * y12) / 2 * x02_ - (x02_ * x02 + y02_ * y02) / 2 * x12_) / D;

    return Vector2f( cx, cy );
}

bool Triangle::is_point_in_circumcircle( Vector2f p )
{
    double a11 = p0.x - p.x;
    double a21 = p1.x - p.x;
    double a31 = p2.x - p.x;

    double a12 = p0.y - p.y;
    double a22 = p1.y - p.y;
    double a32 = p2.y - p.y;

    double a13 = (p0.x - p.x) * (p0.x - p.x) + (p0.y - p.y) * (p0.y - p.y);
    double a23 = (p1.x - p.x) * (p1.x - p.x) + (p1.y - p.y) * (p1.y - p.y);
    double a33 = (p2.x - p.x) * (p2.x - p.x) + (p2.y - p.y) * (p2.y - p.y);

    double det = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31 - a12 * a21 * a33
        - a11 * a23 * a32;

    if ( is_ccw() )
    {
        return det > 0.0;
    }

    return det < 0.0;
}

ClosestEdgeResult Triangle::get_closest_edge_to( Vector2f pr)
{
    Edge e01 = { p0, p1 };
    Edge e12 = { p1, p2 };
    Edge e20 = { p2, p0 };

    float dist01 = Vector2f::distance( Edge::closes_point_to( e01, pr ), pr );
    float dist12 = Vector2f::distance( Edge::closes_point_to( e12, pr ), pr );
    float dist20 = Vector2f::distance( Edge::closes_point_to( e20, pr ), pr );

    if ( dist01 < dist12 )
    {
        if ( dist01 < dist20 )
            return { e01, dist01 };
        else
            return { e20, dist20 };
    }
    else
    {
        if ( dist12 < dist20 )
            return { e12, dist12 };
        else
            return { e20, dist20 };
    }
}

inline bool Triangle::has_vertex( Vector2f pr )
{
    return p0 == pr || p1 == pr || p2 == pr;
}

inline bool Triangle::is_neighbour_to( Edge e )
{
    return (p0 == e.p0 || p1 == e.p0 || p2 == e.p0) && (p0 == e.p1 || p1 == e.p1 || p2 == e.p1);
}

inline Vector2f Triangle::get_opposing_point( Edge e )
{
    if ( (e.p0 == p1 || e.p0 == p2) && (e.p1 == p1 || e.p1 == p2) ) return p0;
    if ( (e.p0 == p0 || e.p0 == p2) && (e.p1 == p0 || e.p1 == p2) ) return p1;
    return p2;
}

inline bool Triangle::is_ccw()
{
    return (p0.x - p2.x) * (p1.y - p2.y) - (p0.y - p2.y) * (p1.x - p2.x) > 0.0;
}

ENGINE_NAMESPACE_END
