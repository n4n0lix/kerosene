// Header
#include "buffertoken.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

BufferToken::BufferToken(uint32 id, void* buffer)
{ 
    _buffer = buffer;
    _id = id;
    _valid = false;
}

void* BufferToken::get_buffer() 
{ 
    return _buffer; 
}

uint32 BufferToken::get_id()
{
    return _id;
}

bool BufferToken::valid()
{
    return _valid;
}

void BufferToken::invalidate() {
    _valid = false;
}

void BufferToken::validate() {
    _valid = true;
}

Range BufferToken::atom_range()
{ 
    return _atomRange; 
}

Range BufferToken::object_range()
{ 
    return _objRange;
}

uint32 BufferToken::object_size()
{
    return _objSize;
}

Vector<uint32> BufferToken::object_indices()
{
    Vector<uint32> objIndices;

    if (_objRange.length() > 0) {
        for (uint32 i = _objRange.index(); i <= _objRange.last_index(); i++) {
            objIndices.push_back(i);
        }
    }

    return std::move(objIndices);
}

bool BufferToken::operator!=(const BufferToken& o) const
{
    return _id != o._id || _buffer != o._buffer;
}

bool BufferToken::operator==(const BufferToken& o) const
{
    return !(*this != o);
}


void BufferToken::set_object_size(uint32 objSize)
{
    _objSize = objSize;
    update();
}

void BufferToken::move(uint32 distance)
{
    _atomRange.move(distance);
    update();
}

void BufferToken::set_atom_range(Range range)
{
    _atomRange = range;
    update();
}

void BufferToken::update()
{
    _objRange = Range(_atomRange.index() / _objSize, 
                      _atomRange.length() / _objSize);
}

ENGINE_NAMESPACE_END

