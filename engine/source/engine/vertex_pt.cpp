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
}

VertexLayout Vertex_pt::layout() const
{
    return{ { {"vec3", "position",  1}, 
              {"vec2", "texcoords", 2} } };
}

vector<float> Vertex_pt::data() const
{
    vector<float> data;
    data.reserve(5);
    data.push_back(position.x);
    data.push_back(position.y);
    data.push_back(position.z);
    data.push_back(texcoords.x);
    data.push_back(texcoords.y);
    return std::move(data);
}

inline uint32 Vertex_pt::bytesize() const 
{ 
    return 3 * FLOAT_BYTES + 2 * FLOAT_BYTES; 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

