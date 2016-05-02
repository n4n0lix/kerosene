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

uint32 BufferToken::atom_index()
{ 
    return _atomIndex; 
}

uint32 BufferToken::atom_length() 
{ 
    return _atomLength; 
}

uint32 BufferToken::object_index()
{ 
    return _objIndex;
}

uint32 BufferToken::object_length() 
{ 
    return _objLength; 
}

uint32 BufferToken::object_size()
{
    return _atomLength / _objLength;
}

shared_ptr<vector<uint32>> BufferToken::object_indices()
{
    return _objIndices;
}

void BufferToken::set_data(uint32 atomIndex, uint32 atomLength, uint32 objSize)
{
    _atomIndex = atomIndex;
    _atomLength = atomLength;
    _objIndex = _atomIndex / objSize;
    _objLength = _atomLength / objSize;

    _objIndices = make_shared<vector<uint32>>();
    for (uint32 i = _objIndex; i < _objIndex + _objLength; i++) {
        _objIndices->push_back(i);
    }
}

bool BufferToken::operator!=(const BufferToken& o) const
{
    return _id != o._id || _buffer != o._buffer;
}

bool BufferToken::operator==(const BufferToken& o) const
{
    return !(*this != o);
}
ENGINE_NAMESPACE_END

