#include "stdafx.h"
#include "vertex_pc.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vertex_pc::Vertex_pc(Vector3f position, Vector4f color) : Vertex()
{
    this->position = position;
    this->color = color;

    layout = { { { "vec3", "position", 1 },
                 { "vec4", "color",    2 } } };

    // Data Vector
    data = vector<float>();
    data.reserve( 7 );
    data.push_back( position.x );
    data.push_back( position.y );
    data.push_back( position.z );
    data.push_back( color.x );
    data.push_back( color.y );
    data.push_back( color.z );
    data.push_back( color.w );

    // Byte size
    bytesize = 3 * FLOAT_BYTES + 4 * FLOAT_BYTES;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
//
//// Header
//#include "vertex_pc.h"
//
//ENGINE_NAMESPACE_BEGIN
//
//Vertex_pc::Vertex_pc( Vector3f position, Vector4f color ) : Vertex(), position( position ), color( color )
//{
//    // Vertex Layout
//    layout = { { { "vec3", "position", 1 },
//    { "vec4", "color",    2 } } };
//
//    // Data Vector
//    data = vector<float>( 7 );
//    data.push_back( position.x );
//    data.push_back( position.y );
//    data.push_back( position.z );
//    data.push_back( color.x );
//    data.push_back( color.y );
//    data.push_back( color.z );
//    data.push_back( color.w );
//
//    // Byte size
//    bytesize = 3 * FLOAT_BYTES + 4 * FLOAT_BYTES;
//}
//
//
//ENGINE_NAMESPACE_END
//
