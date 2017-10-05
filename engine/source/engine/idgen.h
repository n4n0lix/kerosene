#pragma once

// Std-Includes

// Other Includes

// Internal Includes

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class IDGen
{
public:
    inline uint32 new_id() { return ++_nextId; }

private:
    uint32 _nextId;
};

ENGINE_NAMESPACE_END

