// Header
#include "buffertoken2.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

BufferToken2::BufferToken2(uint32 id, void* buffer)
{ 
    _buffer = buffer;
    _id = id;
}

void* BufferToken2::get_buffer() 
{ 
    return _buffer; 
}

uint32 BufferToken2::get_id()
{
    return _id;
}

ENGINE_NAMESPACE_END

