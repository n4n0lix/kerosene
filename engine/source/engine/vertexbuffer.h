#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <ostream>

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "_renderdefs.h"

#include "arraybuffer.h"
#include "vertexlayout.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class VERTEX>
class VertexBuffer : public ArrayBuffer<VERTEX>
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                        VertexBuffer(shared_ptr<VertexLayout> layout, uint32 initCapacity);
                                        ~VertexBuffer();

            GLuint                      get_id();

            shared_ptr<BufferToken>     add_vertices(list<VERTEX> vertices);
            void                        remove_vertices(shared_ptr<BufferToken> token);
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    virtual void                        write(uint32 index, list<VERTEX> vertices);
    virtual void                        remove(uint32 index, uint32 length);
    virtual void                        resize(uint32 oldCapacity, uint32 newCapacity);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GLuint         _vboId;

    shared_ptr<VertexLayout> _layout;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            GLuint                      createVBO(uint32 capacityBytes);

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
VertexBuffer<VERTEX>::VertexBuffer(shared_ptr<VertexLayout> layout, uint32 initCapacity) : ArrayBuffer<VERTEX>((uint32)layout->bytesize(), initCapacity) {
    _layout = layout;

    _vboId = createVBO(atom_capacity());
    LOGGER.log(Level::DEBUG, _vboId) << "CREATE" << endl;
}

template<class VERTEX>
inline VertexBuffer<VERTEX>::~VertexBuffer()
{
    LOGGER.log(Level::DEBUG, _vboId) << "DELETE" << endl;
    glDeleteBuffers( 1, &_vboId );
}

template<class VERTEX>
GLuint VertexBuffer<VERTEX>::get_id()
{
    return _vboId;
}

template<class VERTEX>
shared_ptr<BufferToken> VertexBuffer<VERTEX>::add_vertices(list<VERTEX> vertices)
{
    LOGGER.log(Level::DEBUG, _vboId) << "ADD " << vertices.size() << " vertices" << endl;
    return ArrayBuffer<VERTEX>::write(std::move( vertices ));
}

template<class VERTEX>
void VertexBuffer<VERTEX>::remove_vertices(shared_ptr<BufferToken> token)
{
    ArrayBuffer<VERTEX>::remove(token);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
void VertexBuffer<VERTEX>::write(uint32 index, list<VERTEX> vertices) {
    // vertices -> vector<float>
    vector<float> data;
    for (VERTEX vertex : vertices) {
        vector<float> vertexData = vertex.data();
        data.insert(data.end(), vertexData.begin(), vertexData.end());

        std::ostringstream debugMsg;
        debugMsg << "WRITE VERTEX ["; for (float flt : vertexData) { debugMsg << flt << " "; } debugMsg << "]";
        LOGGER.log(Level::DEBUG) << debugMsg.str() << endl;
    }

    // vector<float> -> gpu-buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferSubData(GL_ARRAY_BUFFER, index, data.size() * FLOAT_BYTES, data.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<class VERTEX>
void VertexBuffer<VERTEX>::remove(uint32 index, uint32 length) {
    // Do nothing
}

template<class VERTEX>
void VertexBuffer<VERTEX>::resize(uint32 oldCapacity, uint32 newCapacity)
{
    // 1# Create temporary copy of VBO
    GLuint tempVboId = createVBO(oldCapacity);

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
GLuint VertexBuffer<VERTEX>::createVBO(uint32 capacityBytes) {
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, capacityBytes, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}

template<class VERTEX>
Logger VertexBuffer<VERTEX>::LOGGER = Logger("VertexBuffer<>", Level::DEBUG);

ENGINE_NAMESPACE_END