#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <vector>
        using std::vector;

// Other Includes

// Internal Includes
#include "_global.h"
#include "vertex.h"
#include "shader.h"
#include "vector2f.h"
#include "vector3f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

/**
 * layout:
 *     vec3 position;
 *     vec2 texcoords;
 */
struct Vertex_pt : Vertex
{
public:

                    Vertex_pt(Vector3f position = Vector3f(0, 0, 0), Vector2f texcoords = Vector2f(0, 0));
                    virtual ~Vertex_pt() = default;

    virtual vector<float>   data()     const;

    Vector3f position;
    Vector2f texcoords;

};

ENGINE_NAMESPACE_END
