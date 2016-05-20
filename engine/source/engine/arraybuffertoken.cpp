// Header
#include "arraybuffertoken.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ArrayBufferToken::ArrayBufferToken(uint32 uid, void * buffer) : BufferToken(uid, buffer)
{

}

void ArrayBufferToken::set_range_id(uint32 rangeId) {
    _rangeId = rangeId;
}

uint32 ArrayBufferToken::range_id()
{
    return _rangeId;
}

ENGINE_NAMESPACE_END


