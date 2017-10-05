// Header
#include "vertex_pt.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Vertex_pt::Vertex_pt(Vector3f position, Vector2f texcoords) : Vertex()
{
    this->position = position;
    this->texcoords = texcoords;

    //
    layout = { { { "vec3", "position",  1 },
                 { "vec2", "texcoords", 2 } } };

    // Data Vector
    data = vector<float>();
    data.reserve( 5 );
    data.push_back( position.x );
    data.push_back( position.y );
    data.push_back( position.z );
    data.push_back( texcoords.x );
    data.push_back( texcoords.y );

    // Byte size
    bytesize = 3 * FLOAT_BYTES + 2 * FLOAT_BYTES;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

//// Header
//#include "vertex_pt.h"
//
//ENGINE_NAMESPACE_BEGIN
//
//Vertex_pt::Vertex_pt( Vector3f position, Vector2f texcoords ) : Vertex(), position( position ), texcoords( texcoords )
//{
//    // Vertex Layout
//
//    // Data Vector
//    data = vector<float>( 5 );
//    data.push_back( position.x );
//    data.push_back( position.y );
//    data.push_back( position.z );
//    data.push_back( texcoords.x );
//    data.push_back( texcoords.y );
//
//    // Byte size
//    bytesize = 3 * FLOAT_BYTES + 2 * FLOAT_BYTES;
//}
//
//ENGINE_NAMESPACE_END
//
