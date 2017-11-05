#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

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
    // Enabled:
    GLBuffer() = default;  // Constructor
    ~GLBuffer() = default;  // Destructor

    void    native_create( GLuint initCapacity );
    void    native_bind();
    void    native_write_at( GLuint index, std::vector<T> data );
    void    native_copy( GLuint src, GLuint dest, GLuint length );
    void    native_resize( GLuint oldCapacity, GLuint newCapacity );
    void    native_delete();
    void    native_unbind();

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
    LOGGER.log( Level::DEBUG ) << "Write " << data.size() << " vertices at [" << index << "]\n";

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
    LOGGER.log( Level::DEBUG ) << "Resize[" << oldCapacity << "]->[" << newCapacity << "]\n";

    // 1# Create temporary copy of IBO
    GLuint tempId = native_allocate( oldCapacity );

    // 2# Copy content into temporary VBO
    glBindBuffer( GL_COPY_READ_BUFFER, _id );
    glBindBuffer( GL_COPY_WRITE_BUFFER, tempId );
    glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity );

    // 3# Resize VBO
    glBindBuffer( TYPE, _id );
    glBufferData( TYPE, newCapacity, NULL, GL_STATIC_DRAW );

    // 4# Copy content back into original VBO
    glBindBuffer( GL_COPY_READ_BUFFER, tempId );
    glBindBuffer( GL_COPY_WRITE_BUFFER, _id );
    glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity );

    // 5# Cleanup
    glDeleteBuffers( 1, &tempId );
    glBindBuffer( TYPE, 0 );
    glBindBuffer( GL_COPY_READ_BUFFER, 0 );
    glBindBuffer( GL_COPY_WRITE_BUFFER, 0 );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_delete()
{
    LOGGER.log( Level::DEBUG ) << "Delete[" << _id << "]\n";
    glDeleteBuffers( 1, &_id );
}

template<typename T, GLuint TYPE>
void GLBuffer<T, TYPE>::native_unbind()
{
    glBindBuffer( TYPE, 0 );
}

template<typename T, GLuint TYPE>
GLuint GLBuffer<T, TYPE>::native_allocate( GLuint initCapacity )
{
    GLuint id;
    glGenBuffers( 1, &id );
    glBindBuffer( TYPE, id );
    glBufferData( TYPE, initCapacity, NULL, GL_STATIC_DRAW );
    glBindBuffer( TYPE, 0 );

    LOGGER.log( Level::DEBUG ) << "Allocate[" << initCapacity << "]\n";
    return id;
}

template<typename T, GLuint TYPE>
Logger GLBuffer<T, TYPE>::LOGGER = Logger( "GLBuffer<>", Level::DEBUG );

ENGINE_NAMESPACE_END

