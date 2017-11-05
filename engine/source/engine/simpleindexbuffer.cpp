#include "stdafx.h"
#include "simpleindexbuffer.h"

ENGINE_NAMESPACE_BEGIN

SimpleIndexBuffer::SimpleIndexBuffer() : _size(0), _capacity(0), _end(0)
{
    native_create( (GLuint)_capacity );
}

SimpleIndexBuffer::~SimpleIndexBuffer()
{
    native_delete();
}

void SimpleIndexBuffer::add_indices( std::vector<uint32> indices )
{
    // #1 Resize if needed
    size_t neededCapacity = _end + indices.size();

    if ( neededCapacity < _capacity ) {
        size_t newCapacity = _capacity + RESIZE_BUFFER_SIZE;
        while ( newCapacity < neededCapacity ) {
            newCapacity += RESIZE_BUFFER_SIZE;
        }

        native_resize( (GLuint)_capacity, (GLuint)newCapacity );
    }

    // 2# Write data
    native_write_at( (GLuint)_end, indices );
    _end += indices.size();
}

ENGINE_NAMESPACE_END

