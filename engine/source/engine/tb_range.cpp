// Header
#include "tb_range.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TB_Range::TB_Range()
    : _buffer(nullptr), _id(0), _index(0), _length(0)
{
}

TB_Range::TB_Range(uint32 id, void* buffer, uint32 index, uint32 length)
    : _buffer(buffer), _id(id), _index(index), _length(length)
{
}

uint32 TB_Range::id() {
    return _id;
}

uint32 TB_Range::index() {
    return _index;
}

uint32 TB_Range::length() {
    return _length;
}

bool TB_Range::operator!=(const TB_Range& o) const
{
    return _id != o._id || _buffer != o._buffer;
}

bool TB_Range::operator==(const TB_Range& o) const
{
    return !(*this != o);
}

ENGINE_NAMESPACE_END


