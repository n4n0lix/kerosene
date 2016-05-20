// Header
#include "stackbuffertoken.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

StackBufferToken::StackBufferToken(uint32 uid, void * buffer) : BufferToken(uid, buffer)
{

}

void StackBufferToken::set_range_id(uint32 rangeId) {
    _rangeId = rangeId;
}

uint32 StackBufferToken::range_id()
{
    return _rangeId;
}

ENGINE_NAMESPACE_END


