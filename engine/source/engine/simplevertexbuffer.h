#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <ostream>
#include <stdexcept>
#include <functional>

// Other Includes

// Std-Extensions

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "_renderdefs.h"
#include "noncopyable.h"

#include "glbuffer.h"
#include "logger.h"

#include "range.h"
#include "vertexlayout.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class VERTEX>
class SimpleVertexBuffer : public GLBuffer<float, GL_ARRAY_BUFFER>
{
    static_assert(std::is_base_of<Vertex, VERTEX>::value, "Template parameter is not a Vertex type!");
public:
                SimpleVertexBuffer(VertexLayout layout);
                ~SimpleVertexBuffer();

    std::vector<uint32>    add_vertices( std::vector<VERTEX> vertices );
    size_t                 size();

    void                   native_vbo_layout();

    using GLBuffer<float, GL_ARRAY_BUFFER>::native_bind;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_copy;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_create;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_resize;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_write_at;

private:
    size_t _size;
    size_t _atomCapacity;
    size_t _atomEnd;

    VertexLayout _layout;

    static Logger LOGGER;    
    static const uint32 RESIZE_BUFFER_SIZE = 1024;

};

template<class VERTEX>
SimpleVertexBuffer<VERTEX>::SimpleVertexBuffer(VertexLayout layout) :
    _layout(layout), _size(0), _atomCapacity(0),
    _atomEnd(0)
{
    native_create( (GLuint)_atomCapacity );
}

template<class T>
SimpleVertexBuffer<T>::~SimpleVertexBuffer()
{
    native_delete();
}

template<class T>
std::vector<uint32> SimpleVertexBuffer<T>::add_vertices( std::vector<T> vertices)
{
    Guard( vertices.size() > 0 ) return std::vector<uint32>();

    std::vector<float> data;
    for ( auto vertex : vertices ) {
        data.insert( data.end(), vertex.data.begin(), vertex.data.end() );
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
    _size += vertices.size();

    // 3# Return indices
    std::vector<uint32> indices;
    for ( size_t i = writeStart; i < _atomEnd; ++i ) {
        indices.push_back( (uint32)i );
    }

    return indices;
}

template<class VERTEX>
size_t SimpleVertexBuffer<VERTEX>::size()
{
    return _size;
}

template<class VERTEX>
void SimpleVertexBuffer<VERTEX>::native_vbo_layout()
{
    GLuint offset = 0;
    for ( VertexComponent component : _layout.components() ) {
        glEnableVertexAttribArray( component.position );
        glVertexAttribPointer( (GLuint)component.position, (GLuint)component.num_components(), component.gltype(), false, (GLuint)_layout.bytesize(), BUFFER_OFFSET( offset ) );
        offset += (GLuint)component.bytesize();
    }
}

template<class VERTEX>
Logger SimpleVertexBuffer<VERTEX>::LOGGER = Logger( "SimpleVertexBuffer<" + typeid(VERTEX).name() + ">", Level::WARN );

ENGINE_NAMESPACE_END