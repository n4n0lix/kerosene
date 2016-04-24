#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes
#include "_gl.h"

// Internal Includes
#include "_global.h"
#include "_renderdefs.h"
#include "vertexbuffer.h"
#include "primitivetype.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class VERTEX>
class DLL_PUBLIC VertexArray
{

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                explicit VertexArray(std::shared_ptr<VertexLayout> layout);

    void                                setVertexBuffer(std::shared_ptr<VertexBuffer<VERTEX>> vertexBuffer);
    shared_ptr<VertexBuffer<VERTEX>>    getVertexBuffer();

    void                                render(shared_ptr<WOB_Token> token);
    void                                render();
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GLuint _vaoId;

    vector<shared_ptr<WOB_Token>>       _renderTokens;
    shared_ptr<VertexLayout>            _layout;
    shared_ptr<VertexBuffer<VERTEX>>    _vertexBuffer;

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

    // #2 Create VBO
    setVertexBuffer(make_shared<VertexBuffer<VERTEX>>(_layout, 32));
}

template<class VERTEX>
void VertexArray<VERTEX>::setVertexBuffer(shared_ptr<VertexBuffer<VERTEX>> vertexBuffer)
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
}

template<class VERTEX>
shared_ptr<VertexBuffer<VERTEX>> VertexArray<VERTEX>::getVertexBuffer()
{
    return _vertexBuffer;
}

template<class VERTEX>
void VertexArray<VERTEX>::render(shared_ptr<WOB_Token> token)
{
    _renderTokens.push_back(token);
}

template<class VERTEX>
void VertexArray<VERTEX>::render()
{
    // 1# Commit changes
    _vertexBuffer->commit();

    // 2# Get indices to display
    vector<uint32> indices;

    for (shared_ptr<WOB_Token> token : _renderTokens) {
        if (token->valid()) {
            vector<uint32>& tokenIndices = *(token->object_indices().get());
            indices.insert(indices.end(), tokenIndices.begin(), tokenIndices.end());
        }
    }

    _renderTokens.clear();

    // 3# Render
    if (indices.empty()) { return; }

    glBindVertexArray(_vaoId);
    glDrawElements(PrimitiveType::TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, &indices[0]);
    glBindVertexArray(0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class VERTEX>
Logger VertexArray<VERTEX>::LOGGER = Logger("VertexArray<>", Level::DEBUG);

ENGINE_NAMESPACE_END

