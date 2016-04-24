#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"
#include "wob_token.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class OBJECT>
class WriteOnlyBuffer
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                WriteOnlyBuffer(uint32 objSize, uint32 objCapacity);


            uint32                   object_size() const;
            uint32                   object_capacity() const;
            uint32                   atom_capacity() const;

    virtual shared_ptr<WOB_Token>    write(shared_ptr<vector<OBJECT>> objects) = 0;
    virtual void                     remove(shared_ptr<WOB_Token> token) = 0;
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            void                     set_atom_capacity(uint32 newAtomCapacity);

    virtual void                     write(uint32 index, shared_ptr<vector<OBJECT>> objects) = 0;
    virtual void                     remove(uint32 index, uint32 length) = 0;
    virtual void                     resize(uint32 oldCapacity, uint32 newCapacity) = 0;

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
WriteOnlyBuffer<OBJECT>::WriteOnlyBuffer(uint32 objSize, uint32 objCapacity)
{ 
    _atomCapacity = objSize * objCapacity;
    _objectSize = objSize;
}

template <class OBJECT>
void WriteOnlyBuffer<OBJECT>::set_atom_capacity(uint32 newAtomCapacity) 
{
    _atomCapacity = newAtomCapacity; 
}

template<class OBJECT>
uint32 WriteOnlyBuffer<OBJECT>::object_size() const 
{ 
    return _objectSize; 
}

template<class OBJECT>
inline uint32 WriteOnlyBuffer<OBJECT>::object_capacity() const 
{ 
    return _atomCapacity / _objectSize; 
}

template<class OBJECT>
inline uint32 WriteOnlyBuffer<OBJECT>::atom_capacity() const
{
    return _atomCapacity; 
}

ENGINE_NAMESPACE_END

