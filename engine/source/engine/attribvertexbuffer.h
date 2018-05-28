#pragma once

// Std-Includes
#include <type_traits>

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_renderdefs.h"
#include "_global.h"
#include "gltype.h"
#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"
#include "matrix4f.h"

#include "glbuffer.h"



ENGINE_NAMESPACE_BEGIN

class AttribVertexBuffer : GLBuffer<float, GL_ARRAY_BUFFER>
{
public:
    AttribVertexBuffer(GLType type, uint32 attribLocation);
    ~AttribVertexBuffer();

    template<typename VAL>
    std::vector<uint32>    add( std::vector<VAL> objs );
    size_t                 size();

    void                   native_attrib_location( uint32 attribLocation );

    using GLBuffer<float, GL_ARRAY_BUFFER>::native_bind;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_copy;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_create;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_resize;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_write_at;

private:
    GLType _type;
    uint32 _attribLocation;

    size_t _size;
    size_t _atomCapacity;
    size_t _atomEnd;

    static Logger LOGGER;
    static const uint32 RESIZE_BUFFER_SIZE = 1024;
};

template<typename VAL>
std::vector<uint32> AttribVertexBuffer::add( std::vector<VAL> objs )
{
    Guard( objs.size() > 0 ) return std::vector<uint32>();

    std::vector<float> data;

    // For float values just copy the data 1:1
    if constexpr(std::is_same_v<VAL, float>) {
        data.insert( data.end(), objs.begin(), objs.end() );
    }
    else {
        for ( auto obj : objs ) write_into( data, obj );
    }

    // 1# Resize if necessary
    size_t neededAtomCapacity = _atomEnd + data.size();
    if ( neededAtomCapacity > _atomCapacity ) {
        size_t newAtomCapacity = _atomCapacity + RESIZE_BUFFER_SIZE;

        while ( newAtomCapacity < neededAtomCapacity ) {
            newAtomCapacity += RESIZE_BUFFER_SIZE;
        }

        native_resize( (GLuint)_atomCapacity, (GLuint)newAtomCapacity );
    }

    // 2# Write to native
    size_t writeStart = _atomEnd;
    native_write_at( (GLuint)_atomEnd, data );
    _atomEnd += data.size();
    _size += objs.size();

    // 3# Return indices
    std::vector<uint32> indices;
    for ( size_t i = (writeStart / _typeComponents); i < (_atomEnd / _typeComponents); ++i ) {
        indices.push_back( (uint32)i );
    }

    return indices;
}



ENGINE_NAMESPACE_END
