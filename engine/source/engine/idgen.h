#pragma once

ENGINE_NAMESPACE_BEGIN

class IDGen
{
public:
    IDGen() = default;
    inline uint32 new_id() { return ++_nextId; }

private:
    uint32 _nextId;
};

ENGINE_NAMESPACE_END