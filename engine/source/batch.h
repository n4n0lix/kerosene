#pragma once

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
#include "_renderdefs.h"
#include "engineexception.h"
#include "vertex.h"
#include "shader.h"
#include "primitivetype.h"
#include "material.h"
#include "dynamicbuffer.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class VERTEX>
class DLL_PUBLIC Batch : DynamicBuffer<VERTEX>
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    INLINE          explicit Batch(shared_ptr<Material> material);

    INLINE void render(PrimitiveType type) const;
    INLINE void addVertices(vector<VERTEX> vertices);

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    INLINE virtual void        write(uint32_t index, vector<VERTEX> objects);
    INLINE virtual void        remove(uint32_t index, uint32_t length);
    INLINE virtual void        resize(uint32_t oldCapacity, uint32_t newCapacity);

    using DynamicBuffer<VERTEX>::write;
    using DynamicBuffer<VERTEX>::remove;
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    GLuint _vaoId;

    GLuint _vboId;
    GLuint _vboByteSize;
    GLuint _vboNumVertices;

    shared_ptr<Material> _material;
    shared_ptr<Shader>   _shader;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class VERTEX>
Batch<VERTEX>::Batch(shared_ptr<Material> material) : DynamicBuffer<VERTEX>((uint32_t) material->getShader()->getVertexLayout().bytesize()) {
    _material = material;
    _shader = material->getShader();

    // VAO
    glGenVertexArrays(1, &_vaoId);
    glBindVertexArray(_vaoId);

        // VBO
        glGenBuffers(1, &_vboId);
        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
        glBufferData(GL_ARRAY_BUFFER, capacity(), NULL, GL_STATIC_DRAW);

        VertexLayout layout = _shader->getVertexLayout();

        GLuint offset = 0;
        for (VertexComponent component : layout.comps) {
            glEnableVertexAttribArray(component.position);
            glVertexAttribPointer(component.position, component.components(), component.gltype(), false, layout.bytesize(), BUFFER_OFFSET(offset));
            offset += component.bytesize();
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

template<class VERTEX>
void Batch<VERTEX>::render(PrimitiveType type) const
{
    _material->getShader()->bind();

    glBindVertexArray(_vaoId);
    glDrawArrays(type, 0, _vboNumVertices);
    glBindVertexArray(0);
}

template<class VERTEX>
void Batch<VERTEX>::addVertices(vector<VERTEX> vertices)
{
    if (vertices.empty()) {
        return;
    }

    write(vertices);
}

template<class VERTEX>
void Batch<VERTEX>::write(uint32_t index, vector<VERTEX> vertices)
{
    // 1# Check if vertex matches the shaders vertex layout
    VertexLayout layout = vertices[0].layout();
    if (layout != _material->getShader()->getVertexLayout()) {
        throw EngineException("Given vertices doesn't match the shaders vertex layout!");
    }

    // 2# Write objects into buffer
    // vertices -> vector<float>
    vector<float> data;
    for (vector<VERTEX>::iterator vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
        vector<float> vertexData = vertex->data();
        data.insert(data.end(), vertexData.begin(), vertexData.end());
    }

    // vector<float> -> gpu-buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferSubData(GL_ARRAY_BUFFER, index, data.size() * FLOAT_BYTES, &data[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 3# Update member variables
    _vboNumVertices += (uint32_t) vertices.size();
}

template<class VERTEX>
void Batch<VERTEX>::remove(uint32_t index, uint32_t length)
{
    // Do nothing
}

template<class VERTEX>
void Batch<VERTEX>::resize(uint32_t oldCapacity, uint32_t newCapacity)
{
    // 1# Create new larger vertexbuffer
    GLuint newVboId;

    GLuint oldVboId = _vboId;

    glGenBuffers(1, &newVboId);
    glBindBuffer(GL_ARRAY_BUFFER, newVboId);
    glBufferData(GL_ARRAY_BUFFER, newCapacity, NULL, GL_STATIC_DRAW);

    // 2# Copy old vertexbuffer in new vertexbuffer
    glBindBuffer(GL_COPY_READ_BUFFER, oldVboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, newVboId);

    glBufferData(GL_COPY_WRITE_BUFFER, newCapacity, nullptr, GL_STATIC_DRAW);

    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);
}

ENGINE_NAMESPACE_END
