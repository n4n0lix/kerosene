#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <algorithm>
        using std::transform;

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "_renderdefs.h"
#include "logger.h"
#include "engineexception.h"
#include "vertex.h"
#include "shader.h"
#include "primitivetype.h"
#include "material.h"
#include "dynamicbuffer.h"
#include "vertexarray.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Inner Classes                      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T> class Batch;

class BatchToken {
    template<class T> friend class Batch;

private:
    BatchToken(void* batch, shared_ptr<BufferToken> token) : _batch(batch), _wobToken(token) { }

    void*                       get_batch()     { return _batch; }
    shared_ptr<BufferToken>     get_wob_token() { return _wobToken; }

    void*                       _batch;
    shared_ptr<BufferToken>     _wobToken;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class VERTEX>
class Batch
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
              explicit Batch(shared_ptr<Material> material);

    void                     render(shared_ptr<BatchToken> token);
    void                     render();

    shared_ptr<BatchToken>   addVertices(shared_ptr<vector<VERTEX>> vertices);
    void                     removeVertices(shared_ptr<BatchToken> token);

    void                     addIndices(shared_ptr<vector<uint32>> indices);
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    unique_ptr<VertexArray<VERTEX>> _vao;

    shared_ptr<Material> _material;
    shared_ptr<Shader>   _shader;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class VERTEX>
Batch<VERTEX>::Batch(shared_ptr<Material> material) {
    _material = material;
    _shader = material->getShader();
    _vao = make_unique<VertexArray<VERTEX>>(_shader->getVertexLayout());
}

template<class VERTEX>
void Batch<VERTEX>::render(shared_ptr<BatchToken> token)
{
    if (token->get_batch() == this) {
        _vao->render(token->get_wob_token());
    }
}


template<class VERTEX>
void Batch<VERTEX>::render()
{
    _material->getShader()->bind();
    _vao->render();
}

template<class VERTEX>
shared_ptr<BatchToken> Batch<VERTEX>::addVertices(shared_ptr<vector<VERTEX>> vertices)
{
    if (vertices->empty()) {
        return nullptr;
    }

    shared_ptr<BufferToken> token = _vao->getVertexBuffer()->addVertices(vertices);

    // 2# Retrieve indices
    shared_ptr<vector<uint32>> indices = make_shared<vector<uint32>>();
    for (uint32 i = token->object_index(); i < token->object_index() + token->object_length(); i++) {
        indices->push_back(i);
    }

    return shared_ptr<BatchToken>(new BatchToken(this, token));
}

template<class VERTEX>
void Batch<VERTEX>::removeVertices(shared_ptr<BatchToken> token)
{
    if (token->_batch != this) {
        LOGGER.log(Level::WARN) << "Invalid token given, token doesn't belong to this batch!" << endl;
        return;
    }

    _vao->getVertexBuffer()->removeVertices(token->_wobToken);
}

template<class VERTEX>
void Batch<VERTEX>::addIndices(shared_ptr<vector<uint32>> indices)
{
    _vao->get_index_buffer()->add_indices(indices);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
Logger Batch<T>::LOGGER = Logger("Batch<>", Level::DEBUG);

ENGINE_NAMESPACE_END
