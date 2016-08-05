#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"
#include "buffertoken.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class OBJECT>
class Buffer
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                     Buffer(uint32 objSize, uint32 objCapacity);

            uint32                   object_size() const;
            uint32                   object_capacity() const;
            uint32                   atom_capacity() const;

    virtual uint32                   num_objects() = 0;
    virtual bool                     contains(shared_ptr<BufferToken> token) = 0;

    virtual shared_ptr<BufferToken>  write(Vector<OBJECT> objects) = 0;
    virtual void                     remove(shared_ptr<BufferToken> token) = 0;
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            void                     set_atom_capacity(uint32 newAtomCapacity);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    uint32 _objectSize;
    uint32 _atomCapacity;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template <class OBJECT>
Buffer<OBJECT>::Buffer(uint32 objSize, uint32 objCapacity)
{ 
    _atomCapacity = objSize * objCapacity;
    _objectSize = objSize;
}

template <class OBJECT>
void Buffer<OBJECT>::set_atom_capacity(uint32 newAtomCapacity) 
{
    _atomCapacity = newAtomCapacity; 
}

template<class OBJECT>
uint32 Buffer<OBJECT>::object_size() const 
{ 
    return _objectSize; 
}

template<class OBJECT>
inline uint32 Buffer<OBJECT>::object_capacity() const 
{ 
    return _atomCapacity / _objectSize; 
}

template<class OBJECT>
inline uint32 Buffer<OBJECT>::atom_capacity() const
{
    return _atomCapacity; 
}

ENGINE_NAMESPACE_END

