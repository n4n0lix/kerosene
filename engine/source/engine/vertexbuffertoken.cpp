// Header
#include "vertexbuffertoken.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

VertexBufferToken::VertexBufferToken(uint32 uid, void* buffer)
{
    _buffer = buffer;
    _id = uid;
    _valid = false;
}

void VertexBufferToken::set_range_id(uint32 rangeId) {
    _rangeId = rangeId;
}

uint32 VertexBufferToken::range_id()
{
    return _rangeId;
}

void* VertexBufferToken::get_buffer()
{
    return _buffer;
}

uint32 VertexBufferToken::get_id()
{
    return _id;
}

bool VertexBufferToken::valid()
{
    return _valid;
}

void VertexBufferToken::invalidate() {
    _valid = false;
}

void VertexBufferToken::validate() {
    _valid = true;
}

Range VertexBufferToken::atom_range()
{
    return _atomRange;
}

Range VertexBufferToken::object_range()
{
    return _objRange;
}

uint32 VertexBufferToken::object_size()
{
    return _objSize;
}

list<uint32> VertexBufferToken::object_indices()
{
    list<uint32> objIndices;

    if (_objRange.length() > 0) {
        for (uint32 i = _objRange.index(); i <= _objRange.last_index(); i++) {
            objIndices.push_back(i);
        }
    }

    return std::move(objIndices);
}

bool VertexBufferToken::operator!=(const VertexBufferToken& o) const
{
    return _id != o._id || _buffer != o._buffer;
}

bool VertexBufferToken::operator==(const VertexBufferToken& o) const
{
    return !(*this != o);
}


void VertexBufferToken::set_object_size(uint32 objSize)
{
    _objSize = objSize;
    update();
}

void VertexBufferToken::move(uint32 distance)
{
    _atomRange.move(distance);
    update();
}

void VertexBufferToken::set_atom_range(Range range)
{
    _atomRange = range;
    update();
}

void VertexBufferToken::update()
{
    _objRange = Range(_atomRange.index() / _objSize,
        _atomRange.length() / _objSize);
}

ENGINE_NAMESPACE_END

