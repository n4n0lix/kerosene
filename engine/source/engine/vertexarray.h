#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes


// Internal Includes
#include "_global.h"
#include "_renderdefs.h"
#include "_gl.h"
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
class VertexArray
{

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                explicit VertexArray(s_ptr<VertexLayout> layout);
                ~VertexArray();

    s_ptr<VertexToken>					add_vertices(list<VERTEX> vertices);
    void                                remove_vertices(s_ptr<VertexToken> token);

    void                                add_render_static(s_ptr<VertexToken> token);
    void                                remove_render_static(s_ptr<VertexToken> token);

    void                                render();
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                                write_new_indices_into_indexbuffer();

    void                                set_vertexbuffer(s_ptr<VertexBuffer<VERTEX>> vertexbuffer);
    void                                set_indexbuffer(s_ptr<IndexBuffer> indexbuffer);

    GLuint _vaoId;

    vector<s_ptr<VertexToken>>     _vertexTokens;
    s_ptr<VertexLayout>            _layout;
    s_ptr<VertexBuffer<VERTEX>>    _vertexBuffer;
    s_ptr<IndexBuffer>             _indexBuffer;

    list<s_ptr<VertexToken>>       _toAddToIndexBuffer;

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
VertexArray<VERTEX>::VertexArray(s_ptr<VertexLayout> layout) : _vertexTokenNextId(0), _layout(layout)
{
    // 0# Contract Pre
    Requires( layout != nullptr );
    
    // #1 Create VAO
    glGenVertexArrays(1, &_vaoId);
    LOGGER.log(Level::DEBUG, _vaoId) << "CREATE" << endl;

    // #2 Create VBO and IxBO
    set_vertexbuffer(make_shared<VertexBuffer<VERTEX>>( _layout, DEFAULT_VERTEXBUFFER_SIZE ));
    set_indexbuffer(make_shared<IndexBuffer>( DEFAULT_INDEXBUFFER_SIZE ));
}

template<class VERTEX>
inline VertexArray<VERTEX>::~VertexArray()
{
    LOGGER.log(Level::DEBUG, _vaoId) << "DELETE" << endl;
    glDeleteVertexArrays( 1, &_vaoId);
}

template<class VERTEX>
s_ptr<VertexToken> VertexArray<VERTEX>::add_vertices(list<VERTEX> vertices) {
    // 1# Add vertices
    s_ptr<BufferToken> vertexBufferToken = _vertexBuffer->add_vertices( vertices );

    // 2# Assemble VertexToken
    s_ptr<VertexToken> vertexToken = make_shared<VertexToken>(_vertexTokenNextId++);
    vertexToken->set_vertexbuffer_token( vertexBufferToken );

    // X# Contract Post
    Ensures( vertexToken != nullptr );
    Ensures( vertexBufferToken != nullptr );
    // TODO: Ensures vertexBufferToken is in vertexbuffer

    return vertexToken;
}

template<class VERTEX>
void VertexArray<VERTEX>::remove_vertices(s_ptr<VertexToken> token) {
    // 0# Contract Pre
    Requires( token != nullptr );
    Requires( token->vertexbuffer_token() != nullptr );

    // 1# Remove from indexbuffer
    if (token->indexbuffer_token() != nullptr) {
        _indexBuffer->remove_indices( token->indexbuffer_token() );
    }

    // 2# Remove from vertexbuffer
    _vertexBuffer->remove_vertices( token->vertexbuffer_token() );

    // X# Contract Post
    // TODO:
    Ensures( _vertexBuffer )
    // Ensure token not in vertexbuffer
    // Ensure token not in indexbuffer
}

template<class VERTEX>
void VertexArray<VERTEX>::add_render_static(s_ptr<VertexToken> token)
{
    // 0# Contract Pre
    Requires(token != nullptr);
    Requires(token->vertexbuffer_token() != nullptr);

    _toAddToIndexBuffer.add( token );
}

template<class VERTEX>
void VertexArray<VERTEX>::remove_render_static(s_ptr<VertexToken> token)
{
    // 0# Contract Pre
    Requires( token != nullptr );
    // TODO: Requires indexBufferToken is in indexbuffer

    // 1# Guards
    Guard( !token->indexbuffer_token() ) return;

    // 2# If indices aren't in indexbuffer yet but in queue for it, just remove them from the queue.
    if (_toAddToIndexBuffer.contains( token )) {
        _toAddToIndexBuffer.remove( token );
        return;
    }

    // 3# Remove indices from indexbuffer
    _indexBuffer->remove_indices( token->indexbuffer_token() );

    // X# Contract Post
    // TODO:
    // Ensure token is not in indexbuffer
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
    glBindVertexArray(_vaoId);
    glDrawElements(PrimitiveType::TRIANGLES, (GLsizei)_indexBuffer->num_objects(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    glBindVertexArray(0);
}

template<class VERTEX>
void VertexArray<VERTEX>::write_new_indices_into_indexbuffer() {
    // 1# Add indices to indexbuffer
    for (auto token : _toAddToIndexBuffer) {
        if (!token->vertexbuffer_token()->valid()) {
            LOGGER.log(Level::WARN, _vaoId) << " trying to add indices of invalid vertextoken (vertices not written to vertexbuffer yet -> no indices)!" << endl; continue;
        }

        auto indexToken = _indexBuffer->add_indices(token->vertexbuffer_token()->object_indices());
        token->set_indexbuffer_token(indexToken);
    }
    _toAddToIndexBuffer.clear();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// TODO: Add nullptr handling -> unbind old vbo
template<class VERTEX>
void VertexArray<VERTEX>::set_vertexbuffer(s_ptr<VertexBuffer<VERTEX>> vertexBuffer)
{
    LOGGER.log(Level::DEBUG, _vaoId) << "BIND VBO (id:" << vertexBuffer->get_id() << ")" << endl;

    // #1 Set vertexbuffer
    _vertexBuffer = vertexBuffer;

    // #2 Bind vertexbuffer
    glBindVertexArray(_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->get_id());

    // #3 Declare VBO Layout
    GLuint offset = 0;
    for (VertexComponent component : _layout->components) {
        LOGGER.log(Level::DEBUG, _vaoId) << "ATTR (pos:" << component.position << ", num:" << component.components() << ", glt:" << component.gltype() << ", off:" << offset << ")" << endl;
        glEnableVertexAttribArray(component.position);
        glVertexAttribPointer(component.position, component.components(), component.gltype(), false, _layout->bytesize(), BUFFER_OFFSET(offset));
        offset += component.bytesize();
    }

    // #3 Cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<class VERTEX>
void VertexArray<VERTEX>::set_indexbuffer(s_ptr<IndexBuffer> indexBuffer)
{
    LOGGER.log(Level::DEBUG, _vaoId) << "BIND IxBO (id:" << indexBuffer->get_id() << ")" << endl;

    // #1 Set indexbuffer
    _indexBuffer = indexBuffer;

    // #2 Bind indexbuffer
    glBindVertexArray(_vaoId);
    if (_indexBuffer != nullptr) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->get_id());
    }
    else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // 3# Cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
Logger VertexArray<VERTEX>::LOGGER = Logger("VertexArray<>", Level::DEBUG);

template<class VERTEX>
uint32 VertexArray<VERTEX>::DEFAULT_VERTEXBUFFER_SIZE = 32;

template<class VERTEX>
uint32 VertexArray<VERTEX>::DEFAULT_INDEXBUFFER_SIZE = 32;

ENGINE_NAMESPACE_END

