// Header
#include "tb_token.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TB_Token::TB_Token(uint32 uid, void * buffer) : BufferToken(uid, buffer)
{

}

void TB_Token::set_range_id(uint32 rangeId) {
    _rangeId = rangeId;
}

uint32 TB_Token::range_id()
{
    return _rangeId;
}

ENGINE_NAMESPACE_END


