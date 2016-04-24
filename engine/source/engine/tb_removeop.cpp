// Header
#include "tb_removeop.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TB_RemoveOp::TB_RemoveOp(uint32 id, shared_ptr<TB_Token> token)
{
    _id = id;
    _token = token;
}

uint32 TB_RemoveOp::id()
{
    return _id;
}

shared_ptr<TB_Token> TB_RemoveOp::token()
{
    return _token;
}

ENGINE_NAMESPACE_END


