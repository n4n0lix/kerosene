#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"
#include "stackbuffertoken.h"
#include "vertexbuffertoken.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class VertexToken {
public:
            explicit VertexToken(uint32 id);
            ~VertexToken() = default;

    uint32  id();

    void                      set_vertexbuffer_token(weak<VertexBufferToken> token);
    weak<VertexBufferToken>   vertexbuffer_token();

    void                      set_indexbuffer_token(weak<StackBufferToken> token);
    weak<StackBufferToken>    indexbuffer_token();
private:
    uint32 _id;
    weak<VertexBufferToken>   _tokenVertexBuffer;
    weak<StackBufferToken>    _tokenIndexBuffer;
};

ENGINE_NAMESPACE_END