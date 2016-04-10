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
#include "vertexarray.h"

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
                INLINE VertexBuffer(shared_ptr<VertexLayout> layout, uint32_t initCapacity);

    INLINE GLuint                           getId();

    INLINE unique_ptr<DynamicBufferToken>   addVertices(vector<VERTEX> vertices);
    INLINE void                             removeVertices(unique_ptr<DynamicBufferToken> token);

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    INLINE virtual void        write(uint32_t index, vector<VERTEX> vertices);
    INLINE virtual void        remove(uint32_t index, uint32_t length);
    INLINE virtual void        resize(uint32_t oldCapacity, uint32_t newCapacity);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GLuint         _vboId;

    shared_ptr<VertexLayout> _layout;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    INLINE static GLuint createVBOWithLayout(uint32_t capacityBytes);

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
VertexBuffer<VERTEX>::VertexBuffer(shared_ptr<VertexLayout> layout, uint32_t initCapacity) : DynamicBuffer<VERTEX>((uint32_t)layout->bytesize(), initCapacity) {
    _layout = layout;

    _vboId = createVBOWithLayout(capacity());
    LOGGER.log(DEBUG_RENDERING, _vboId) << "CREATE" << endl;
}

template<class VERTEX>
inline GLuint VertexBuffer<VERTEX>::getId()
{
    return _vboId;
}

template<class VERTEX>
unique_ptr<DynamicBufferToken> VertexBuffer<VERTEX>::addVertices(vector<VERTEX> vertices)
{
    LOGGER.log(DEBUG_RENDERING, _vboId) << "WRITE " << vertices.size() << " vertices" << endl;
    return move(DynamicBuffer<VERTEX>::write(vertices));
}

template<class VERTEX>
void VertexBuffer<VERTEX>::removeVertices(unique_ptr<DynamicBufferToken> token)
{
    DynamicBuffer<VERTEX>::remove(swap(token));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
void VertexBuffer<VERTEX>::write(uint32_t index, vector<VERTEX> vertices) {
    // vertices -> vector<float>
    vector<float> data;
    for (vector<VERTEX>::iterator vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
        vector<float> vertexData = vertex->data();
        data.insert(data.end(), vertexData.begin(), vertexData.end());

        LOGGER.log(DEBUG_RENDERING, _vboId) << "WRITE [";
        for (float flt : vertexData) {
            LOGGER.log_(DEBUG_RENDERING) << flt << " ";
        }
        LOGGER.log_(DEBUG_RENDERING) << "]" << endl;
    }

    // vector<float> -> gpu-buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    GLint size;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    LOGGER.log(DEBUG_RENDERING) << "size: " << size << endl;
    glBufferSubData(GL_ARRAY_BUFFER, 0, 84, &data[0]);
    //glBufferSubData(GL_ARRAY_BUFFER, index, data.size() * FLOAT_BYTES, &data[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<class VERTEX>
void VertexBuffer<VERTEX>::remove(uint32_t index, uint32_t length) {
    // Do nothing
}

template<class VERTEX>
void VertexBuffer<VERTEX>::resize(uint32_t oldCapacity, uint32_t newCapacity)
{
    // 1# Create temporary copy of VBO
    GLuint tempVboId = createVBOWithLayout(oldCapacity);

    // 2# Copy content into temporary VBO
    glBindBuffer(GL_COPY_READ_BUFFER, _vboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, tempVboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);

    // 3# Resize VBO
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, newCapacity, NULL, GL_STATIC_DRAW);

    // 4# Copy content back into original VBO
    glBindBuffer(GL_COPY_READ_BUFFER, tempVboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, _vboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);

    // 5# Cleanup
    glDeleteBuffers(1, &tempVboId);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
GLuint VertexBuffer<VERTEX>::createVBOWithLayout(uint32_t capacityBytes) {
    GLuint vboId;

    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, capacityBytes, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}

template<class VERTEX>
Logger VertexBuffer<VERTEX>::LOGGER = Logger("VertexBuffer<>");

ENGINE_NAMESPACE_END