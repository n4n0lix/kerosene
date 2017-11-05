#pragma once

// Std-Includes
#include <ostream>

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"

#include "glbuffer.h"

ENGINE_NAMESPACE_BEGIN

class SimpleIndexBuffer : public GLBuffer<uint32, GL_ELEMENT_ARRAY_BUFFER>
{
public:
            explicit SimpleIndexBuffer();
            ~SimpleIndexBuffer();

    void    add_indices( std::vector<uint32> indices );

    using GLBuffer<uint32, GL_ELEMENT_ARRAY_BUFFER>::native_bind;
    using GLBuffer<uint32, GL_ELEMENT_ARRAY_BUFFER>::native_copy;
    using GLBuffer<uint32, GL_ELEMENT_ARRAY_BUFFER>::native_create;
    using GLBuffer<uint32, GL_ELEMENT_ARRAY_BUFFER>::native_resize;
    using GLBuffer<uint32, GL_ELEMENT_ARRAY_BUFFER>::native_write_at;

private:
    size_t          _size;
    size_t          _capacity;
    size_t          _end;

    static const uint32 RESIZE_BUFFER_SIZE = 1024;
};

ENGINE_NAMESPACE_END