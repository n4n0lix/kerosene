// Header
#include "tb_removeop.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TB_RemoveOp::TB_RemoveOp(uint32 id, shared_ptr<BufferToken> token)
{
    _id = id;
    _token = token;
}

uint32 TB_RemoveOp::id()
{
    return _id;
}

shared_ptr<BufferToken> TB_RemoveOp::token()
{
    return _token;
}

ENGINE_NAMESPACE_END


