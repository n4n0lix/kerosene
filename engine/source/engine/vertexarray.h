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
    explicit                            VertexArray(shared_ptr<VertexLayout> layout);

    void                                set_vertexbuffer(shared_ptr<VertexBuffer<VERTEX>> vertexBuffer);
    shared_ptr<VertexBuffer<VERTEX>>    get_vertexbuffer();

    void                                set_indexbuffer(shared_ptr<IndexBuffer> indexBuffer);
    shared_ptr<IndexBuffer>             get_indexbuffer();

    void                                render(shared_ptr<BufferToken> token);
    void                                render();
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                                clean_up_rendering();

    void                                render_by_vbotokens();
    void                                render_by_indexbuffer();

    GLuint _vaoId;

    vector<shared_ptr<BufferToken>>     _renderTokens;
    shared_ptr<VertexLayout>            _layout;
    shared_ptr<VertexBuffer<VERTEX>>    _vertexBuffer;
    shared_ptr<IndexBuffer>             _indexBuffer;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
VertexArray<VERTEX>::VertexArray(shared_ptr<VertexLayout> layout)
{
    _layout = layout;
    
    // #1 Create VAO
    glGenVertexArrays(1, &_vaoId);
    LOGGER.log(Level::DEBUG, _vaoId) << "CREATE" << endl;

    // #2 Create VBO and IxBO
    set_vertexbuffer(make_shared<VertexBuffer<VERTEX>>(_layout, 32));
    set_indexbuffer(make_shared<IndexBuffer>(32));
}

// TODO: Add nullptr handling -> unbind old vbo
template<class VERTEX>
void VertexArray<VERTEX>::set_vertexbuffer(shared_ptr<VertexBuffer<VERTEX>> vertexBuffer)
{
    LOGGER.log(Level::DEBUG, _vaoId) << "BIND VBO (id:" << vertexBuffer->getId() << ")" << endl;

    // #1 Set vertexbuffer
    _vertexBuffer = vertexBuffer;

    // #2 Bind vertexbuffer
    glBindVertexArray(_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());

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
shared_ptr<VertexBuffer<VERTEX>> VertexArray<VERTEX>::get_vertexbuffer()
{
    return _vertexBuffer;
}

template<class VERTEX>
void VertexArray<VERTEX>::set_indexbuffer(shared_ptr<IndexBuffer> indexBuffer)
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

template<class VERTEX>
inline shared_ptr<IndexBuffer> VertexArray<VERTEX>::get_indexbuffer()
{
    return _indexBuffer;
}

template<class VERTEX>
void VertexArray<VERTEX>::render(shared_ptr<BufferToken> token)
{
    _renderTokens.push_back(token);
}

template<class VERTEX>
void VertexArray<VERTEX>::render()
{
    // 1# Commit changes
    _vertexBuffer->commit();
    _indexBuffer->commit();

    // 2# Render
    if (_indexBuffer == nullptr) {
        render_by_vbotokens();
    }
    else {
        render_by_indexbuffer();
    }

    clean_up_rendering();
}

template<class VERTEX>
void VertexArray<VERTEX>::clean_up_rendering()
{
    _renderTokens.clear();
}

template<class VERTEX>
void VertexArray<VERTEX>::render_by_vbotokens()
{    
    // 1# Construct 'cpu index buffer' from tokens
    vector<uint32> indices;

    for (shared_ptr<BufferToken> token : _renderTokens) {
        if (token->valid()) {
            vector<uint32>& tokenIndices = *(token->object_indices().get());
            indices.insert(indices.end(), tokenIndices.begin(), tokenIndices.end());
        }
    }

    // 2# Render
    glBindVertexArray(_vaoId);
    glDrawElements(PrimitiveType::TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, &indices[0]);
    glBindVertexArray(0);
}

template<class VERTEX>
void VertexArray<VERTEX>::render_by_indexbuffer()
{
    // 1# Render
    glBindVertexArray(_vaoId);
    glDrawElements(PrimitiveType::TRIANGLES, (GLsizei)_indexBuffer->num_objects(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    glBindVertexArray(0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
Logger VertexArray<VERTEX>::LOGGER = Logger("VertexArray<>", Level::DEBUG);

ENGINE_NAMESPACE_END

