// Header
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
}

VertexLayout Vertex_pc::layout() const
{
    return{ { {"vec3", "position", 1}, 
              {"vec4", "color",    2} } };
}

vector<float> Vertex_pc::data() const
{
    vector<float> data;
    data.reserve(7);
    data.push_back(position.x);
    data.push_back(position.y);
    data.push_back(position.z);
    data.push_back(color.x);
    data.push_back(color.y);
    data.push_back(color.z);
    data.push_back(color.w);
    return data;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

