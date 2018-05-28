#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes


// Internal Includes
#include "_global.h"
#include "_stdext.h"
#include "_renderdefs.h"
#include "_gl.h"
#include "perfstats.h"

#include "vertex.h"
#include "vertexlayout.h"
#include "primitivetype.h"

#include "simplevertexbuffer.h"
#include "simpleindexbuffer.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class VERTEX>
class SimpleVertexArray : public noncopyable
{
    static_assert(std::is_base_of<Vertex, VERTEX>::value, "Template parameter is not a Vertex type!");

public:
    SimpleVertexArray();
    ~SimpleVertexArray();

    optional<SimpleVertexBuffer<VERTEX>>& get_vertex_buffer();
    optional<SimpleIndexBuffer>&          get_index_buffer();

    void                render_by_indexbuffer();
    void                render_all();

private:
    void                native_create();
    void                native_delete();
    void                native_bind();
    void                native_unbind();

    void                create_vertexbuffer();
    void                create_indexbuffer();

    GLuint                                  _id;
    VertexLayout                            _layout;
    optional<SimpleVertexBuffer<VERTEX>>    _vertexBuffer;
    optional<SimpleIndexBuffer>             _indexBuffer;
};

template<class VERTEX>
SimpleVertexArray<VERTEX>::SimpleVertexArray() :
    _vertexBuffer( std::nullopt ),
    _indexBuffer( std::nullopt )
{
    VERTEX v;
    _layout = v.layout;

    native_create();

    create_vertexbuffer();
    create_indexbuffer();
}

template<class VERTEX>
void SimpleVertexArray<VERTEX>::native_create()
{
    glGenVertexArrays( 1, &_id );

    glBindVertexArray( _id );
    for ( VertexComponent component : _layout.components() ) {
        glEnableVertexAttribArray( component.position );
    }
    glBindVertexArray( 0 );
}

template<class VERTEX>
SimpleVertexArray<VERTEX>::~SimpleVertexArray()
{
    native_delete();
}

template<class VERTEX>
optional<SimpleVertexBuffer<VERTEX>>& SimpleVertexArray<VERTEX>::get_vertex_buffer()
{
    return _vertexBuffer;
}

template<class VERTEX>
optional<SimpleIndexBuffer>& SimpleVertexArray<VERTEX>::get_index_buffer()
{
    return _indexBuffer;
}


template<class VERTEX>
void SimpleVertexArray<VERTEX>::native_delete()
{
    glDeleteVertexArrays( 1, &_id );
}

template<class VERTEX>
void SimpleVertexArray<VERTEX>::native_bind()
{
    glBindVertexArray( _id );
}

template<class VERTEX>
void SimpleVertexArray<VERTEX>::native_unbind()
{
    glBindVertexArray( 0 );
}

template<class VERTEX>
void SimpleVertexArray<VERTEX>::render_by_indexbuffer() {
    glBindVertexArray( _id );
    glDrawElements( (GLuint)PrimitiveType::TRIANGLES, (GLsizei)_indexBuffer->size() , GL_UNSIGNED_INT, BUFFER_OFFSET( 0 ) );
    glBindVertexArray( 0 );

    PerfStats::instance().frame_draw_call( _indexBuffer->size() );
}

template<class VERTEX>
void SimpleVertexArray<VERTEX>::render_all() {
    glBindVertexArray( _id );
    glDrawArrays( (GLuint)PrimitiveType::TRIANGLES, 0, (GLsizei)_vertexBuffer->size() );
    glBindVertexArray( 0 );

    PerfStats::instance().frame_draw_call( _vertexBuffer->size() / 3 );
}

template<class VERTEX>
void SimpleVertexArray<VERTEX>::create_vertexbuffer()
{
    _vertexBuffer.emplace( _layout );

    native_bind();
    _vertexBuffer->native_bind();
    _vertexBuffer->native_vbo_layout();

    native_unbind();
    _vertexBuffer->native_unbind();
}

template<class VERTEX>
void SimpleVertexArray<VERTEX>::create_indexbuffer()
{
    _indexBuffer.emplace();

    native_bind();
    _indexBuffer->native_bind();

    native_unbind();
    _indexBuffer->native_unbind();
}

ENGINE_NAMESPACE_END


