// Header
#include "bufferrange.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

BufferRange::BufferRange()
    : _buffer(nullptr), _id(0), _index(0), _length(0)
{
}

BufferRange::BufferRange(uint32 id, void* buffer, uint32 index, uint32 length)
    : _buffer(buffer), _id(id), _index(index), _length(length)
{
}

uint32 BufferRange::id() {
    return _id;
}

uint32 BufferRange::index() {
    return _index;
}

uint32 BufferRange::length() {
    return _length;
}

uint32 BufferRange::last_index() {
    return _index + _length - 1;
}

bool BufferRange::operator!=(const BufferRange& o) const
{
    return _id != o._id || _buffer != o._buffer;
}

bool BufferRange::operator==(const BufferRange& o) const
{
    return !(*this != o);
}

ENGINE_NAMESPACE_END


