#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"
#include "buffertoken.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class VertexToken {
public:
    VertexToken(uint32 id);

    uint32                  id();

    void                    set_vertexbuffer_token(shared_ptr<BufferToken> token);
    shared_ptr<BufferToken> vertexbuffer_token();

    void                    set_indexbuffer_token(shared_ptr<BufferToken> token);
    shared_ptr<BufferToken> indexbuffer_token();
private:
    uint32 _id;
    shared_ptr<BufferToken> _tokenVertexBuffer;
    shared_ptr<BufferToken> _tokenIndexBuffer;
};

ENGINE_NAMESPACE_END