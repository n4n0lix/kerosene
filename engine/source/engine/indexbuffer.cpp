// Header
#include "indexbuffer.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

IndexBuffer::IndexBuffer(uint32 initCapacity) : StackBuffer<uint16>(1, initCapacity) {
    _iboId = createIBO(atom_capacity() * UINT16_BYTES);
    LOGGER.log(Level::DEBUG, _iboId) << "CREATE [0," << atom_capacity()-1 << "]" << endl;
}

GLuint IndexBuffer::get_id()
{
    return _iboId;
}

shared_ptr<BufferToken> IndexBuffer::add_indices(shared_ptr<vector<uint16>> indices)
{
    LOGGER.log(Level::DEBUG, _iboId) << "ADD " << indices->size() << " indices" << endl;
    shared_ptr<BufferToken> token = StackBuffer<uint16>::write(indices);
    _activeTokens.add(token);
    return token;
}

void IndexBuffer::remove_indices(shared_ptr<BufferToken> token)
{
    StackBuffer<uint16>::remove(token);
    _activeTokens.remove(token);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void IndexBuffer::write(uint32 index, shared_ptr<vector<uint16>> indices) {
    // debug only
    std::ostringstream debugMsg;
    debugMsg << "WRITE INDICES [";
    for (uint16 aIndex : *indices.get()) {
        debugMsg << aIndex << " ";
    }
    LOGGER.log(Level::DEBUG) << debugMsg.str() << "]" << endl;

    // vector<float> -> gpu-buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index, indices->size() * FLOAT_BYTES, &indices.get()[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::copy(uint32 srcIndex, uint32 destIndex, uint32 length) {
    LOGGER.log(Level::DEBUG, _iboId) << "COPY [" << srcIndex << "," << srcIndex + length << "] TO [" << destIndex << "," << destIndex + length << "]" << endl;
    // TODO: Implement this
    // 1# Create temporary copy of IBO
    GLuint tempIboId = createIBO(atom_capacity());

    // 2# Copy content into temporary VBO
    glBindBuffer(GL_COPY_READ_BUFFER, _iboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, tempIboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, atom_capacity());

    // 3# Copy source content back to new destination
    glBindBuffer(GL_COPY_READ_BUFFER, tempIboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, _iboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcIndex, destIndex, length);

    // 5# Cleanup
    glDeleteBuffers(1, &tempIboId);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

void IndexBuffer::resize(uint32 oldCapacity, uint32 newCapacity)
{
    // 1# Create temporary copy of IBO
    GLuint tempIboId = createIBO(oldCapacity);

    // 2# Copy content into temporary VBO
    glBindBuffer(GL_COPY_READ_BUFFER, _iboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, tempIboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);

    // 3# Resize VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, newCapacity, NULL, GL_STATIC_DRAW);

    // 4# Copy content back into original VBO
    glBindBuffer(GL_COPY_READ_BUFFER, tempIboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, _iboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);

    // 5# Cleanup
    glDeleteBuffers(1, &tempIboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLuint IndexBuffer::createIBO(uint32 capacityBytes) {
    GLuint iboId;
    glGenBuffers(1, &iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, capacityBytes, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return iboId;
}

Logger IndexBuffer::LOGGER = Logger("IndexBuffer", Level::DEBUG);


ENGINE_NAMESPACE_END

