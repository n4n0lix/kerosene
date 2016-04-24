// Header
#include "wob_token.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

WOB_Token::WOB_Token(uint32 id, void* buffer)
{ 
    _buffer = buffer;
    _id = id;
    _valid = false;
}

void* WOB_Token::get_buffer() 
{ 
    return _buffer; 
}

uint32 WOB_Token::get_id()
{
    return _id;
}

bool WOB_Token::valid()
{
    return _valid;
}

void WOB_Token::invalidate() {
    _valid = false;
}

void WOB_Token::validate() {
    _valid = true;
}

uint32 WOB_Token::atom_index()
{ 
    return _atomIndex; 
}

uint32 WOB_Token::atom_length() 
{ 
    return _atomLength; 
}

uint32 WOB_Token::object_index()
{ 
    return _objIndex;
}

uint32 WOB_Token::object_length() 
{ 
    return _objLength; 
}

shared_ptr<vector<uint32>> WOB_Token::object_indices()
{
    return _objIndices;
}

void WOB_Token::set_data(uint32 atomIndex, uint32 atomLength, uint32 objSize)
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

bool WOB_Token::operator!=(const WOB_Token& o) const
{
    return _id != o._id || _buffer != o._buffer;
}

bool WOB_Token::operator==(const WOB_Token& o) const
{
    return !(*this != o);
}
ENGINE_NAMESPACE_END

