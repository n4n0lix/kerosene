// Header
#include "range.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Range::Range()
    : _start(0), _length(0)
{
}

Range::Range(uint32 start, uint32 length)
    : _start(start), _length(length)
{
}

uint32 Range::start() {
    return _start;
}

uint32 Range::length() {
    return _length;
}

uint32 Range::index() {
    return _start;
}

uint32 Range::last_index() {
    if (_length == 0) {
        return _start;
    }

    return _start + _length - 1;
}

bool Range::operator!=(const Range& o) const
{
    return _start != o._start || _length != _length;
}

bool Range::operator==(const Range& o) const
{
    return !(*this != o);
}

void Range::move(uint32 distance) {
    _start = _start + distance;
}

ENGINE_NAMESPACE_END


