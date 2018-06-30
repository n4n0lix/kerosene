#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <typeinfo>

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "noncopyable.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<typename T, GLuint TYPE = GL_ARRAY_BUFFER>
class GLBuffer : public noncopyable
{
public:
    GLBuffer() = default;
    ~GLBuffer() = default;

    void    native_create( GLuint initCapacity );
    void    native_bind();
    void    native_write_at( GLuint index, std::vector<T> data );
    void    native_copy( GLuint src, GLuint dest, GLuint length );
    void    native_resize( GLuint oldCapacity, GLuint newCapacity );
    void    native_delete();
    void    native_unbind();

    GLuint  gl_id();

    GLuint  native_allocate( GLuint initCapacity );
private:
    GLuint  _id;

    static Logger LOGGER;
};

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_create( GLuint initCapacity )
{
    _id = native_allocate( initCapacity );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_bind()
{
    glBindBuffer( TYPE, _id );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_write_at( GLuint index, std::vector<T> data )
{
    LOGGER.log( Level::DEBUG ) << "[" << _id << "] Write " << data.size() << " objects at [" << index << "]\n";

    glBindBuffer( TYPE, _id );
    glBufferSubData( TYPE, index, (GLuint)(data.size() * sizeof( T )), data.data());
    glBindBuffer( TYPE, 0 );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_copy( GLuint src, GLuint dest, GLuint length )
{
    // 1# Create temporary copy of IBO
    GLuint tempId = native_allocate( length );

    // 2# Copy content into temporary VBO
    glBindBuffer( GL_COPY_READ_BUFFER, _id );
    glBindBuffer( GL_COPY_WRITE_BUFFER, tempId );
    glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcIndex, 0, atom_capacity() );

    // 3# Copy source content back to new destination
    glBindBuffer( GL_COPY_READ_BUFFER, tempId );
    glBindBuffer( GL_COPY_WRITE_BUFFER, _id );
    glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, destIndex, length );

    // 4# Cleanup
    glDeleteBuffers( 1, &tempId );
    glBindBuffer( GL_COPY_READ_BUFFER, 0 );
    glBindBuffer( GL_COPY_WRITE_BUFFER, 0 );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_resize( GLuint oldCapacity, GLuint newCapacity )
{
    LOGGER.log( Level::DEBUG ) << "[" << _id << "] Resize[" << oldCapacity << "]->[" << newCapacity << "]\n";

    // 1# Create temporary copy of IBO
    GLuint tempId = native_allocate( oldCapacity );
    GLuint amountToCopy = std::min( oldCapacity, newCapacity );

    // 2# Copy content into temporary VBO
    glBindBuffer( GL_COPY_READ_BUFFER, _id );
    glBindBuffer( GL_COPY_WRITE_BUFFER, tempId );
    glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, amountToCopy );

    // 3# Resize VBO
    glBindBuffer( TYPE, _id );
    glBufferData( TYPE, newCapacity, NULL, GL_STATIC_DRAW );

    // 4# Copy content back into original VBO
    glBindBuffer( GL_COPY_READ_BUFFER, tempId );
    glBindBuffer( GL_COPY_WRITE_BUFFER, _id );
    glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, amountToCopy );

    // 5# Cleanup
    glDeleteBuffers( 1, &tempId );
    glBindBuffer( TYPE, 0 );
    glBindBuffer( GL_COPY_READ_BUFFER, 0 );
    glBindBuffer( GL_COPY_WRITE_BUFFER, 0 );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_delete()
{
    LOGGER.log( Level::DEBUG ) << "[" << _id << "] Delete[" << _id << "]\n";
    glDeleteBuffers( 1, &_id );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_unbind()
{
    glBindBuffer( TYPE, 0 );
}

template<typename T, GLuint TYPE>
inline GLuint GLBuffer<T, TYPE>::gl_id()
{
    return _id;
}

template<typename T, GLuint TYPE>
GLuint GLBuffer<T, TYPE>::native_allocate( GLuint initCapacity )
{
    GLuint _id;
    glGenBuffers( 1, &_id );
    glBindBuffer( TYPE, _id );
    glBufferData( TYPE, initCapacity, NULL, GL_STATIC_DRAW );
    glBindBuffer( TYPE, 0 );

    LOGGER.log( Level::DEBUG ) << "[" << _id << "] Allocate[" << initCapacity << "]\n";
    return _id;
}

template<typename T, GLuint TYPE>
Logger GLBuffer<T, TYPE>::LOGGER = Logger( string("GLBuffer<") + string(typeid(T).name()) + string(">"), Level::DEBUG );

ENGINE_NAMESPACE_END

