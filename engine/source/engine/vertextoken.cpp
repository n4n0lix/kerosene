#include "stdafx.h"
#include "vertextoken.h"

ENGINE_NAMESPACE_BEGIN

VertexToken::VertexToken(uint32 id) : _id(id)
{
}

uint32 VertexToken::id()
{
    return _id;
}

void VertexToken::set_vertexbuffer_token(weak<VertexBufferToken> token)
{
    _tokenVertexBuffer = token;
}

weak<VertexBufferToken> VertexToken::vertexbuffer_token()
{
    return _tokenVertexBuffer;
}

void VertexToken::set_indexbuffer_token(weak<StackBufferToken> token)
{
    _tokenIndexBuffer = token;
}

weak<StackBufferToken> VertexToken::indexbuffer_token()
{
    return _tokenIndexBuffer;
}

ENGINE_NAMESPACE_END