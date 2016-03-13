#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"
#include "_renderdefs.h"
#include "dynamicbuffer.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class VERTEX>
class DLL_PUBLIC VertexBuffer : public DynamicBuffer<VERTEX>
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit VertexBuffer(VertexLayout layout) : DynamicBuffer(layout.bytesize()) {
                _layout = layout;

                // VBO
                glGenBuffers(1, &_vboId);
                glBindBuffer(GL_ARRAY_BUFFER, _vboId);
                glBufferData(GL_ARRAY_BUFFER, capacity(), NULL, GL_STATIC_DRAW);

                GLuint offset = 0;
                for (VertexComponent component : _layout.comps) {
                    glEnableVertexAttribArray(component.position);
                    glVertexAttribPointer(component.position, component.components(), component.gltype(), false, _layout.bytesize(), BUFFER_OFFSET(offset));
                    offset += component.bytesize();
                }
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

    INLINE void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    }

    INLINE void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    using DynamicBuffer::write;

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    virtual void write(int32_t offset, vector<VERTEX> vertices) {
        // Convert vertices into float vector
        vector<float> data;
        for (vector<VERTEX>::iterator vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
            vector<float> vertexData = vertex->data();
            data.insert(data.end(), vertexData.begin(), vertexData.end());
        }

        // Write the data to the gpu buffer
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * _layout.bytesize(), &data[0]);
        unbind();
    }
    

    virtual void free(int32_t offset, int32_t length) {
        // Do nothing
    }

    virtual void resize(int32_t newCapacity) {
        // Allocate new buffer
        GLuint newVBOId;
        glGenBuffers(1, &newVBOId);
        glBindBuffer(GL_ARRAY_BUFFER, newVBOId);
        glBufferData(GL_ARRAY_BUFFER, newCapacity, NULL, GL_STATIC_DRAW);

        GLuint offset = 0;
        for (VertexComponent component : _layout.comps) {
            glEnableVertexAttribArray(component.position);
            glVertexAttribPointer(component.position, component.components(), component.gltype(), false, _layout.bytesize(), BUFFER_OFFSET(offset));
            offset += component.bytesize();
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Copy old data, if exists
        bool oldBufferExists = _vboId != -1;

        if (oldBufferExists) {
            GLuint oldVBOId = _vboId;

            glBindBuffer(GL_COPY_READ_BUFFER, oldVBOId);
            glBindBuffer(GL_COPY_WRITE_BUFFER, newVBOId);
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, capacity());

            glBindBuffer(GL_COPY_READ_BUFFER, 0);
            glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        }

        _vboId = newVBOId;
    }

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GLuint       _vboId;
    VertexLayout _layout;
};

ENGINE_NAMESPACE_END
