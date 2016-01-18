#ifndef BATCH_H
#define BATCH_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <vector>
        using std::vector;
#include <algorithm>
        using std::transform;

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"
#include "engineexception.h"
#include "vertex.h"
#include "shader.h"
#include "primitivetype.h"
#include "material.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class DLL_PUBLIC Batch
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Batch(shared_ptr<Material> material);

    template<class VERTEX>
    void addVertices(vector<VERTEX> vertices)
    {
        if (vertices.empty()) {
            return;
        }

        // Check if vertex matches the shaders vertex layout
        VertexLayout layout = vertices[0].layout();
        if (layout != _material->getShader()->getVertexLayout()) {
            throw EngineException("Given vertex doesn't match the shaders vertex layout!");
        }

        // Do some calculations
        _vboNumVertices = static_cast<unsigned int>(vertices.size());
        _vboByteSize = static_cast<unsigned int>(vertices.size() * layout.bytesize());

        // Write vertex data into a vector
        vector<float> data;
        for (vector<VERTEX>::iterator vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
            vector<float> vertexData = vertex->data();
            data.insert(data.end(), vertexData.begin(), vertexData.end());
        }

        // Send data to gpu
        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
        glBufferData(GL_ARRAY_BUFFER, _vboByteSize, &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void render(PrimitiveType type) const;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    GLuint _vaoId;

    GLuint _vboId;
    GLuint _vboByteSize;
    GLuint _vboNumVertices;

    shared_ptr<Material> _material;
    shared_ptr<Shader> _shader;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
};

ENGINE_NAMESPACE_END
#endif // BATCH_H
