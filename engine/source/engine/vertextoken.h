#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"
#include "buffertoken.h"
#include "vertexbuffertoken.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class VertexToken {
public:
            explicit VertexToken(uint32 id);
            ~VertexToken() = default;

    uint32                  id();

    void                            set_vertexbuffer_token(shared_ptr<VertexBufferToken> token);
    shared_ptr<VertexBufferToken>   vertexbuffer_token();

    void                            set_indexbuffer_token(shared_ptr<BufferToken> token);
    shared_ptr<BufferToken>         indexbuffer_token();
private:
    uint32 _id;
    shared_ptr<VertexBufferToken>   _tokenVertexBuffer;
    shared_ptr<BufferToken>         _tokenIndexBuffer;
};

ENGINE_NAMESPACE_END