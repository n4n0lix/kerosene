#include "stdafx.h"
#include "simpleindexbuffer.h"

ENGINE_NAMESPACE_BEGIN

SimpleIndexBuffer::SimpleIndexBuffer() : _atomCapacity(0), _end(0)
{
    native_create( (GLuint)_atomCapacity );
}

SimpleIndexBuffer::~SimpleIndexBuffer()
{
    native_delete();
}

void SimpleIndexBuffer::add_indices( std::vector<uint32> indices )
{
    // #1 Resize if needed
    size_t neededCapacity = _end + indices.size() * sizeof(uint32);

    if ( _atomCapacity < neededCapacity ) {
        size_t newAtomCapacity = _atomCapacity + RESIZE_BUFFER_SIZE;
        while ( newAtomCapacity < neededCapacity ) {
            newAtomCapacity += RESIZE_BUFFER_SIZE;
        }

        native_resize( (GLuint)_atomCapacity, (GLuint)newAtomCapacity );
        _atomCapacity = newAtomCapacity;
    }

    // 2# Write data
    native_write_at( (GLuint)_end, indices );
    _end += indices.size();
}

size_t SimpleIndexBuffer::size()
{
    return _end;
}

ENGINE_NAMESPACE_END

