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
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "primitivetype.h"
#include "vertextoken.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class VERTEX>
class VertexArray : public noncopyable
{
    static_assert(std::is_base_of<Vertex, VERTEX>::value, "Template parameter is not a Vertex type!");

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    VertexArray();
    ~VertexArray();

    owner<VertexToken>  add_vertices( std::vector<VERTEX>&& vertices );
    void                remove_vertices( owner<VertexToken> token );

    void                add_render_static( weak<VertexToken> token );
    void                remove_render_static( weak<VertexToken> token );
    void                clear();

    void                render();

    VertexArray<VERTEX>& operator=( VertexArray<VERTEX>&& orig );
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    void                native_render();

    void                write_new_indices_into_indexbuffer();

    void                set_vertexbuffer( owner<VertexBuffer<VERTEX>> vertexbuffer );
    void                set_indexbuffer( owner<IndexBuffer> indexbuffer );

    GLuint _vaoId;

    VertexLayout                   _layout;
    owner<VertexBuffer<VERTEX>>    _vertexBuffer;
    owner<IndexBuffer>             _indexBuffer;

    std::vector<weak<VertexToken>> _toAddToIndexBuffer;

    uint32 _vertexTokenNextId;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
    static uint32 DEFAULT_VERTEXBUFFER_SIZE;
    static uint32 DEFAULT_INDEXBUFFER_SIZE;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
VertexArray<VERTEX>::VertexArray() : _vertexTokenNextId( 0 ), _vertexBuffer(nullptr)
{
    VERTEX v;
    _layout = v.layout;

    // #1 Create VAO
    glGenVertexArrays( 1, &_vaoId );
    LOGGER.log( Level::DEBUG, _vaoId ) << "CREATE\n";

    // #2 Create VBO and IxBO
    set_vertexbuffer( make_owner<VertexBuffer<VERTEX>>( _layout, DEFAULT_VERTEXBUFFER_SIZE ));
    set_indexbuffer( make_owner<IndexBuffer>( DEFAULT_INDEXBUFFER_SIZE ) );
}

template<class VERTEX>
VertexArray<VERTEX>::~VertexArray()
{
    LOGGER.log( Level::DEBUG, _vaoId ) << "DELETE" << "\n";
    glDeleteVertexArrays( 1, &_vaoId );
}

template<class VERTEX>
owner<VertexToken> VertexArray<VERTEX>::add_vertices( std::vector<VERTEX>&& vertices ) {
    // 1# Add vertices
    weak<VertexBufferToken> vertexBufferToken = _vertexBuffer->add_vertices( std::forward<std::vector<VERTEX>>( vertices ) );

    // 2# Assemble VertexToken
    owner<VertexToken> vertexToken = make_owner<VertexToken>( _vertexTokenNextId++ );
    vertexToken->set_vertexbuffer_token( vertexBufferToken );

    // X# Contract Post
    Ensures( vertexToken != nullptr );
    Ensures( vertexBufferToken != nullptr );
    Ensures( _vertexBuffer->contains( vertexBufferToken ) );

    return std::move( vertexToken );
}

template<class VERTEX>
void VertexArray<VERTEX>::remove_vertices( owner<VertexToken> token ) {
    // 0# Contract Pre
    Requires( token != nullptr );
    Requires( token->vertexbuffer_token() != nullptr );

    // 1# Remove from indexbuffer
    if ( token->indexbuffer_token() != nullptr ) {
        _indexBuffer->remove_indices( token->indexbuffer_token() );
    }

    // 2# Remove from vertexbuffer
    _vertexBuffer->remove_vertices( token->vertexbuffer_token() );

    // X# Contract Post
    Ensures( !_vertexBuffer->contains( token->vertexbuffer_token() ) );

    // 3# Destroy token
    token.destroy();
}

template<class VERTEX>
void VertexArray<VERTEX>::add_render_static( weak<VertexToken> token )
{
    // 0# Contract Pre
    Requires( token.is_ptr_valid() );
    Requires( token != nullptr );
    Requires( token->vertexbuffer_token() != nullptr );

    // 1# ...
    _toAddToIndexBuffer.push_back( token );

    // X# Contract Post
    Ensures( ext::contains( _toAddToIndexBuffer, token ) );
}

template<class VERTEX>
void VertexArray<VERTEX>::remove_render_static( weak<VertexToken> token )
{
    // 0# Contract Pre
    Requires( token.is_ptr_valid() );
    Requires( token != nullptr );
    Requires( _indexBuffer->contains( token->indexbuffer_token() )
        || ext::contains( _toAddToIndexBuffer, token ) );

    // 2# If indices aren't in indexbuffer yet but in queue for it, just remove them from the queue.
    auto tokenPos = std::find( _toAddToIndexBuffer.begin(), _toAddToIndexBuffer.end(), token );
    if ( tokenPos != _toAddToIndexBuffer.end() ) {
        _toAddToIndexBuffer.erase( tokenPos );
        return;
    }

    // 3# Remove indices from indexbuffer
    _indexBuffer->remove_indices( token->indexbuffer_token() );

    // X# Contract Post
    Ensures( !_indexBuffer->contains( token->indexbuffer_token() ) );
    Ensures( !ext::contains( _toAddToIndexBuffer, token ) );
}

template<class VERTEX>
inline void VertexArray<VERTEX>::clear()
{
    _vertexBuffer->clear();
    _indexBuffer->clear();
}

template<class VERTEX>
void VertexArray<VERTEX>::render()
{
    // 1# Remove old indices
    _indexBuffer->commit_remove();

    // 2# Remove old vertices
    _vertexBuffer->commit_remove();

    // 3# Write new vertices into vertexbuffer
    _vertexBuffer->commit_write();

    // 4# Write new indices into indexbuffer (dependency on 3#, because of indices from new vertices written in 3#)
    write_new_indices_into_indexbuffer();
    _indexBuffer->commit_write();

    // 6# Render
    native_render();
}

template<class VERTEX>
void VertexArray<VERTEX>::native_render() {
    glBindVertexArray( _vaoId );
    glDrawElements( (int32)PrimitiveType::TRIANGLES, (GLsizei)_indexBuffer->num_objects(), GL_UNSIGNED_INT, BUFFER_OFFSET( 0 ) );
    glBindVertexArray( 0 );

    PerfStats::instance().frame_draw_call( _indexBuffer->num_objects() / 3 );
}

template<class VERTEX>
void VertexArray<VERTEX>::write_new_indices_into_indexbuffer() {
    // 1# Add indices to indexbuffer
    for ( auto token : _toAddToIndexBuffer ) {
        if ( !token->vertexbuffer_token()->valid() ) {
            LOGGER.log( Level::WARN, _vaoId ) << " trying to add indices of invalid vertextoken (vertices not written to vertexbuffer yet -> no indices)!" << "\n"; 
            continue;
        }

        auto indexToken = _indexBuffer->add_indices( token->vertexbuffer_token()->object_indices() );
        token->set_indexbuffer_token( indexToken );
    }
    _toAddToIndexBuffer.clear();
}

template<class VERTEX>
VertexArray<VERTEX>& VertexArray<VERTEX>::operator=( VertexArray<VERTEX>&& orig )
{
    // Move state
    _vaoId  = orig._vaoId;
    _layout = orig._layout;
    _vertexBuffer = std::move( orig._vertexBuffer );
    _indexBuffer  = std::move( orig._indexBuffer );
    _toAddToIndexBuffer = std::move( orig._toAddToIndexBuffer );
    _vertexTokenNextId = orig._vertexTokenNextId;

    // TODO: This will leave it in an invalid state, maybe think about a "nullstate" for vertexarray
    orig._vaoId = 0;
    orig._layout = orig._layout;
    orig._vertexBuffer = nullptr;
    orig._indexBuffer = nullptr;
    orig._toAddToIndexBuffer = std::vector<weak<VertexToken>>();
    orig._vertexTokenNextId = 0;

    return *this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// TODO: Add nullptr handling -> unbind old vbo
template<class VERTEX>
void VertexArray<VERTEX>::set_vertexbuffer( owner<VertexBuffer<VERTEX>> vertexBuffer )
{
    LOGGER.log( Level::DEBUG, _vaoId ) << "BIND VBO (id:" << vertexBuffer->get_id() << ")" << "\n";

    // #1 Set vertexbuffer
    _vertexBuffer = std::move( vertexBuffer );

    // #2 Bind vertexbuffer
    glBindVertexArray( _vaoId );
    glBindBuffer( GL_ARRAY_BUFFER, _vertexBuffer->get_id() );

    // #3 Declare VBO Layout
    GLuint offset = 0;
    for ( VertexComponent component : _layout.components() ) {
        LOGGER.log( Level::DEBUG, _vaoId ) << "ATTR (pos:" << component.position << ", num:" << component.num_components() << ", glt:" << component.gltype() << ", off:" << offset << ")\n"  ;
        glEnableVertexAttribArray( component.position );
        glVertexAttribPointer( (GLuint)component.position, (GLuint)component.num_components(), component.gltype(), false, (GLuint)_layout.bytesize(), BUFFER_OFFSET( offset ) );
        offset += (GLuint)component.bytesize();
    }

    // #3 Cleanup
    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

template<class VERTEX>
void VertexArray<VERTEX>::set_indexbuffer( owner<IndexBuffer> indexBuffer )
{
    LOGGER.log( Level::DEBUG, _vaoId ) << "BIND IxBO (id:" << indexBuffer->get_id() << ")\n";

    // #1 Set indexbuffer
    _indexBuffer = std::move( indexBuffer );

    // #2 Bind indexbuffer
    glBindVertexArray( _vaoId );
    if ( _indexBuffer != nullptr ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->get_id() );
    }
    else {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }

    // 3# Cleanup
    glBindVertexArray( 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
Logger VertexArray<VERTEX>::LOGGER = Logger( "VertexArray<>", Level::DEBUG );

template<class VERTEX>
uint32 VertexArray<VERTEX>::DEFAULT_VERTEXBUFFER_SIZE = 32;

template<class VERTEX>
uint32 VertexArray<VERTEX>::DEFAULT_INDEXBUFFER_SIZE = 32;

ENGINE_NAMESPACE_END

