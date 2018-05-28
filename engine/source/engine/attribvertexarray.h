#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "glvao.h"
#include "vertex.h"
#include "simpleindexbuffer.h"
#include "attribvertexbuffer.h"
#include "gltype.h"

ENGINE_NAMESPACE_BEGIN

template<typename VERTEX>
class AttribVertexArray : GLVAO<VERTEX>
{
    static_assert(std::is_base_of<Vertex, VERTEX>::value, "Template parameter is not a Vertex type!");

public:
    AttribVertexArray();
    ~AttribVertexArray() = default;

    std::vector<uint32>          add_vertices( std::vector<VERTEX> pVertices );
    optional<SimpleIndexBuffer>& get_index_buffer();


    void                render_by_indexbuffer();
    void                render_all();

protected:
    using GLVAO<VERTEX>::native_create;
    using GLVAO<VERTEX>::native_bind;
    using GLVAO<VERTEX>::native_delete;
    using GLVAO<VERTEX>::native_unbind;
    using GLVAO<VERTEX>::id;
    using GLVAO<VERTEX>::layout;

private:
    void                native_layout();

    void                create_vertexbuffers();
    void                create_indexbuffer();

    optional<SimpleIndexBuffer>             _indexBuffer;
    std::vector<owner<AttribVertexBuffer>>  _vertexBuffers;
};

template<typename VERTEX>
AttribVertexArray<VERTEX>::AttribVertexArray() : GLVAO<VERTEX>()
{
    native_create();

    create_vertexbuffers();
    create_indexbuffer();
}

template<typename VERTEX>
std::vector<uint32> AttribVertexArray<VERTEX>::add_vertices( std::vector<VERTEX> pVertices )
{
    VertexLayout& layout = layout();
    layout.num_components();

    for ( auto& vertex : pVertices ) {
        
    }
}

template<typename VERTEX>
optional<SimpleIndexBuffer>& AttribVertexArray<VERTEX>::get_index_buffer()
{
    return _indexBuffer;
}

template<class VERTEX>
void AttribVertexArray<VERTEX>::render_by_indexbuffer() {
    native_bind();
    glDrawElements( (GLuint)PrimitiveType::TRIANGLES, (GLsizei)_indexBuffer->num_objects(), GL_UNSIGNED_INT, BUFFER_OFFSET( 0 ) );
    native_unbind();

    PerfStats::instance().frame_draw_call( _indexBuffer->num_objects() / 3 );
}

template<class VERTEX>
void AttribVertexArray<VERTEX>::render_all() {
    native_bind();
    glDrawArrays( (GLuint)PrimitiveType::TRIANGLES, 0, (GLsizei)_vertexBuffers[0]->size() );
    native_unbind();

    PerfStats::instance().frame_draw_call( _vertexBuffers[0]->size() / 3 );
}

template<typename VERTEX>
void AttribVertexArray<VERTEX>::native_layout()
{
    VertexLayout& layout = layout();

    for ( auto comp : layout.components() ) {
        owner<AttribVertexBuffer> tvbo = _vertexBuffers[ comp.position ];

        if ( vbo == nullptr ) continue;

        native_bind();
        vbo->native_bind();
        vbo->native_vbo_layout();

        native_unbind();
        vbo->native_unbind();
    }
}

template<typename VERTEX>
void AttribVertexArray<VERTEX>::create_vertexbuffers()
{
    _vertexBuffers.reserve( layout().num_components() );

    for ( VertexComponent comp : layout().components() ) {
        GLType& type = GLType::FLOAT;

        if ( comp.type == string( "vec2" ) ) {
            type = GLType::VEC2;
        }
        else if ( comp.type == string( "vec3" ) ) {
            type = GLType::VEC3;
        }
        else if ( comp.type == string( "vec4" ) ) {
            type = GLType::VEC4;
        }
        else if ( comp.type == string( "mat4" ) ) {
            type = GLType::MAT4;
        }

        auto vbo = make_owner<AttribVertexBuffer>( type, comp.position );
        auto pos = _vertexBuffers.begin() + comp.position;
        _vertexBuffers.emplace( pos, std::move( vbo ) );
    }
}

template<typename VERTEX>
void AttribVertexArray<VERTEX>::create_indexbuffer()
{
    _indexBuffer.emplace();

    native_bind();
    _indexBuffer->native_bind();

    native_unbind();
    _indexBuffer->native_unbind();
}

ENGINE_NAMESPACE_END