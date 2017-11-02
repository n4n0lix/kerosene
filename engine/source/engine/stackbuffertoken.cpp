#include "stdafx.h"
#include "stackbuffertoken.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

StackBufferToken::StackBufferToken(uint32 id, void* buffer)
{
    _buffer = buffer;
    id = id;
    _valid = false;
}

void StackBufferToken::set_range_id(uint32 rangeId) {
    _rangeId = rangeId;
}

uint32 StackBufferToken::range_id()
{
    return _rangeId;
}

void* StackBufferToken::get_buffer()
{
    return _buffer;
}

uint32 StackBufferToken::get_id()
{
    return id;
}

bool StackBufferToken::valid()
{
    return _valid;
}

void StackBufferToken::invalidate() {
    _valid = false;
}

void StackBufferToken::validate() {
    _valid = true;
}

Range StackBufferToken::atom_range()
{
    return _atomRange;
}

Range StackBufferToken::object_range()
{
    return _objRange;
}

uint32 StackBufferToken::object_size()
{
    return _objSize;
}

std::vector<uint32> StackBufferToken::object_indices()
{
    std::vector<uint32> objIndices;

    if (_objRange.length() > 0) {
        for (uint32 i = _objRange.index(); i <= _objRange.last_index(); i++) {
            objIndices.push_back(i);
        }
    }

    return std::move( objIndices );
}

bool StackBufferToken::operator!=(const StackBufferToken& o) const
{
    return id != o.id || _buffer != o._buffer;
}

bool StackBufferToken::operator==(const StackBufferToken& o) const
{
    return !(*this != o);
}


void StackBufferToken::set_object_size(uint32 objSize)
{
    _objSize = objSize;
    update();
}

void StackBufferToken::set_atom_range(Range range)
{
    _atomRange = range;
    update();
}

void StackBufferToken::update()
{
    _objRange = Range(_atomRange.index() / _objSize,
        _atomRange.length() / _objSize);
}

ENGINE_NAMESPACE_END


