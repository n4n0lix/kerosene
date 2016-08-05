#include "vertextoken.h"

ENGINE_NAMESPACE_BEGIN

VertexToken::VertexToken(uint32 id) : _id(id)
{
}

uint32 VertexToken::id()
{
    return _id;
}

void VertexToken::set_vertexbuffer_token(shared_ptr<BufferToken> token)
{
    _tokenVertexBuffer = token;
}

shared_ptr<BufferToken> VertexToken::vertexbuffer_token()
{
    return _tokenVertexBuffer;
}

void VertexToken::set_indexbuffer_token(shared_ptr<BufferToken> token)
{
    _tokenIndexBuffer = token;
}

shared_ptr<BufferToken> VertexToken::indexbuffer_token()
{
    return _tokenIndexBuffer;
}

ENGINE_NAMESPACE_END