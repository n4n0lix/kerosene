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
    void                   clear();
    size_t                 size();

    void                   native_vbo_layout();

    using GLBuffer<float, GL_ARRAY_BUFFER>::gl_id;

    using GLBuffer<float, GL_ARRAY_BUFFER>::native_bind;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_copy;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_create;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_resize;
    using GLBuffer<float, GL_ARRAY_BUFFER>::native_write_at;

private:
    size_t _nativeCapacity;
    size_t _nativeEnd;

    VertexLayout _layout;

    static Logger LOGGER;    
    static const uint32 RESIZE_BUFFER_SIZE = 1024;
};

template<class VERTEX>
SimpleVertexBuffer<VERTEX>::SimpleVertexBuffer(VertexLayout layout) :
    _layout(layout), _nativeCapacity(0),
    _nativeEnd(0)
{
    native_create( (GLuint)_nativeCapacity );
    native_bind();
    native_vbo_layout();
    native_unbind();
}

template<class T>
SimpleVertexBuffer<T>::~SimpleVertexBuffer()
{
    native_delete();
}

template<class T>
std::vector<uint32> SimpleVertexBuffer<T>::add_vertices( std::vector<T> vertices)
{
    if( vertices.size() == 0 ) return std::vector<uint32>();

    // 1# Prepare native data
    std::vector<float> nativeData;
    for ( auto vertex : vertices ) {
        nativeData.insert( nativeData.end(), vertex.data.begin(), vertex.data.end() );
    }

    // 2# Resize if necessary
    size_t requiredNativeCapacity = _nativeEnd + nativeData.size() * sizeof(float);
    if ( _nativeCapacity < requiredNativeCapacity ) {
        size_t newNativeCapacity = _nativeCapacity + RESIZE_BUFFER_SIZE;

        while ( newNativeCapacity < requiredNativeCapacity ) {
            newNativeCapacity += RESIZE_BUFFER_SIZE;
        }

        native_resize( (GLuint)_nativeCapacity, (GLuint)newNativeCapacity );
        _nativeCapacity = newNativeCapacity;
    }

    // 3# Write to native
    size_t writeStart = _nativeEnd;
    native_write_at( (GLuint)_nativeEnd, nativeData );
    _nativeEnd += nativeData.size();

    // 4# Return indices
    std::vector<uint32> indices;
    for ( size_t i = writeStart; i < _nativeEnd; ++i ) {
        indices.push_back( (uint32)i );
    }

    return indices;
}

template<class VERTEX>
void SimpleVertexBuffer<VERTEX>::clear()
{
    //native_resize( _nativeCapacity, 0 );

    //_nativeCapacity = 0;
    _nativeEnd = 0;
}

template<class VERTEX>
size_t SimpleVertexBuffer<VERTEX>::size()
{
    uint32 floatsPerObject = _layout.bytesize() / sizeof( float );
    return _nativeEnd / floatsPerObject;
}

template<class VERTEX>
void SimpleVertexBuffer<VERTEX>::native_vbo_layout()
{
    GLuint offset = 0;
    for ( VertexComponent component : _layout.components() ) {
        glVertexAttribPointer( (GLuint)component.position, (GLuint)component.num_components(), component.gltype(), false, (GLuint)_layout.bytesize(), BUFFER_OFFSET( offset ) );
        offset += (GLuint)component.bytesize();
    }
}

template<class VERTEX>
Logger SimpleVertexBuffer<VERTEX>::LOGGER = Logger( "SimpleVertexBuffer<" + typeid(VERTEX).name() + ">", Level::WARN );

ENGINE_NAMESPACE_END