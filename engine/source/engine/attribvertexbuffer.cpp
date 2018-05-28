#include "stdafx.h"
#include "attribvertexarray.h"

ENGINE_NAMESPACE_BEGIN

AttribVertexBuffer::AttribVertexBuffer( GLType pType, uint32 pAttribLocation ) :
    _size( 0 ), _atomCapacity( 0 ), _atomEnd( 0 ),
    _attribLocation( pAttribLocation ), _type( pType )
{
    native_create( (GLuint)(_atomCapacity * _type.numComps) );
    native_bind();
    native_attrib_location( _attribLocation );
    native_unbind();
}

AttribVertexBuffer::~AttribVertexBuffer()
{
    native_delete();
}

size_t AttribVertexBuffer::size()
{
    return _size;
}

void AttribVertexBuffer::native_attrib_location( uint32 attribLoc )
{
    glVertexAttribPointer( (GLuint)attribLoc, (GLuint)_type.numComps, GL_FLOAT, GL_FALSE, (GLuint)_type.byteSize, BUFFER_OFFSET( 0 ) );
}

ENGINE_NAMESPACE_END