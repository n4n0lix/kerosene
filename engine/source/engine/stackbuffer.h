#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <stdexcept>
#include <functional>

// Std-Extensions
#include "vector.h"
#include "map.h"

// Internal Includes
#include "_global.h"
#include "range.h"
#include "transactionalbuffer.h"
#include "stackbuffertoken.h"

// TODO: Optimize the methods 'optimizeNext' and 'optimize'
// TODO: Merge RemoveOps and WriteOps to decrease the num of operations
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
class StackBuffer : public TransactionalBuffer<T>
{

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                            StackBuffer(uint32 objSize, uint32 objCapacity);

    using                                   TransactionalBuffer<T>::commit_write;
    using                                   TransactionalBuffer<T>::commit_remove;
    using                                   TransactionalBuffer<T>::write;
    using                                   TransactionalBuffer<T>::remove;
    using                                   TransactionalBuffer<T>::num_objects;
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    virtual void                            commit_write(Vector<T> objects, shared_ptr<BufferToken> commit_token);
    virtual void                            commit_remove(shared_ptr<BufferToken> token);
        
    virtual shared_ptr<BufferToken>         create_token(uint32 id);
    using                                   TransactionalBuffer::get_tokens;
    using                                   TransactionalBuffer::get_future_tokens;

    // Final-Implementation
    virtual void                            write(uint32 index, Vector<T> objects) = 0;
    virtual void                            resize(uint32 oldCapacity, uint32 newCapacity) = 0;
    virtual void                            copy(uint32 srcIndex, uint32 destIndex, uint32 length) = 0;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            shared_ptr<StackBufferToken>    get_token_by_range_id(uint32 rangeId);

            uint32                          generateRangeId();

    Range                     _freeRange;
    Map<uint32, Range>        _usedRanges; // TODO: Continue here, goal is to remove uid from within BufferRange

    uint32                    _nextUidRange;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
StackBuffer<T>::StackBuffer(uint32 objSize, uint32 objCapacity) : TransactionalBuffer(objSize, objCapacity)
{
    _nextUidRange = 0;

    // 1# Create initial range
    _freeRange = Range(0, atom_capacity());
    LOGGER.log(Level::DEBUG) << "CREATE [" << _freeRange.index() << "," << _freeRange.length()-1 << "], OBJ SIZE: " << object_size()  << endl;

    // X# Contract Post
    Ensures( _freeRange.length() == atom_capacity() );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
void StackBuffer<T>::commit_write(Vector<T> objects, shared_ptr<BufferToken> aToken)
{
    auto token = static_pointer_cast<StackBufferToken>(aToken);

    // 0# Contract Pre
    Requires( objects.size() > 0 );
    Requires( aToken != nullptr );

    // 1# Check if freerange is large enough
    uint32 neededSize = (uint32_t)objects.size() * object_size();
    
    if (_freeRange.length() < neededSize) {
        // ... we need to grow the buffer
        uint32 oldAtomCapacity = atom_capacity();
        uint32 newAtomCapacity = oldAtomCapacity + neededSize;
        uint32 diffAtomCapacity = newAtomCapacity - oldAtomCapacity;

        resize(oldAtomCapacity, newAtomCapacity);
        LOGGER.log(Level::DEBUG) << "RESIZE FROM [" << oldAtomCapacity << "] TO [" << newAtomCapacity << "]" << endl;
        set_atom_capacity(newAtomCapacity);
        
        _freeRange = Range(_freeRange.index(), 
                           _freeRange.index() + diffAtomCapacity);
        LOGGER.log(Level::DEBUG) << "FREE IS [" << _freeRange.index() << ", " << _freeRange.last_index() << "]" << endl;
    }

    // 2# Split of range of 'free range'
    uint32 usedRangeId = generateRangeId();
    Range usedRange = Range(_freeRange.index(), neededSize);
    _freeRange = Range(usedRange.index() + usedRange.length(), _freeRange.length() - usedRange.length());

    // 2#  Write
    LOGGER.log(Level::DEBUG) << "WRITE " << objects.size() << " AT [" << usedRange.index() << ", " << usedRange.index() + neededSize - 1 << "]" << endl;
    LOGGER.log(Level::DEBUG) << "FREE IS [" << _freeRange.index() << ", " << _freeRange.last_index() << "]" << endl;

    write(usedRange.index(), std::move(objects));

    _usedRanges.put(usedRangeId, usedRange);

    // 3# Update and validate the token
    token->set_range_id(usedRangeId);
    token->set_atom_range(usedRange);
    token->set_object_size(object_size());
    token->validate();

    // X# Contract Post
    Ensures( token->valid() );
}

template<class OBJECT>
void StackBuffer<OBJECT>::commit_remove(shared_ptr<BufferToken> aToken)
{
    auto token = static_pointer_cast<StackBufferToken>(aToken);

    // 1# Get used range
    uint32 rangeId = token->range_id();

    if (!_usedRanges.contains(rangeId)) {
        LOGGER.log(Level::DEBUG) << "Attempting to remove unkown range with id: " << rangeId << endl;
        return;
    }
    
    Range range = _usedRanges.get(rangeId);

    // 2# Remove range
    // 2.1# Calculate 'delete' 'copySource' and 'copyDest' ranges
    uint32 delRangeFirst = range.index();
    uint32 delRangeLast = range.last_index();
    uint32 delRangeLength = range.length();

    uint32 copySourceFirst = delRangeLast + 1;
    uint32 copySourceLast = _freeRange.index() - 1;
    uint32 copySourceLength = (copySourceLast - copySourceFirst) + 1;

    uint32 copyDestFirst = delRangeFirst;
    uint32 copyDestLast = delRangeFirst + copySourceLength - 1;
    uint32 copyDestLength = (copyDestLast - copyDestFirst) + 1;

    uint32 freeRangeFirst = copyDestLast + 1;
    uint32 freeRangeLast = atom_capacity()-1;
    uint32 freeRangeLength = (freeRangeLast - freeRangeFirst) + 1;

    uint32 moveDistance = copyDestFirst - copySourceFirst;

    Assert(copyDestFirst <= copySourceFirst);
    Assert(copySourceLength == copyDestLength);

    // 2.2# Copy data
    copy(copySourceFirst, copyDestFirst, copySourceLength);
    LOGGER.log(Level::DEBUG) << "COPY [" << copySourceFirst << ", " << copySourceLast << "] TO [" << copyDestFirst << ", " << copyDestLast << "]" << endl;

    _usedRanges.remove(rangeId);
    _freeRange = Range(freeRangeFirst, freeRangeLength);

    // 2.4# Update all ranges
    for (auto pair : _usedRanges.as_vector()) {
        uint32 id    = pair.first;
        Range  range = pair.second;

        // Determine if range is affected by deletion
        if (range.index() > delRangeLast) {
            // Update Range
            range.move( moveDistance );

            _usedRanges.remove( id );
            _usedRanges.put( id, range );

            // Update Token
            auto token = get_token_by_range_id( id );
            token->set_atom_range( range );

            LOGGER.log(Level::DEBUG) << "UPDATE TOKEN" << endl;
        }
    }

    // 3# Invalidate token
    token->invalidate();
}

template<class T>
shared_ptr<BufferToken> StackBuffer<T>::create_token(uint32 id)
{
    return make_shared<StackBufferToken>(id, this);
}

template<class T>
shared_ptr<StackBufferToken> StackBuffer<T>::get_token_by_range_id(uint32 rangeId)
{
    // 1# Search in tokens
    for (auto aToken : get_tokens()) {
        auto token = static_pointer_cast<StackBufferToken>(aToken);
        if (token->range_id() == rangeId) {
            return token;
        }
    }

    // 2# Search in future tokens
    for (auto aToken : get_future_tokens()) {
        auto token = static_pointer_cast<StackBufferToken>(aToken);
        if (token->range_id() == rangeId) {
            return token;
        }
    }

    return nullptr;
}

template<class T>
uint32 StackBuffer<T>::generateRangeId() {
    return _nextUidRange++;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class OBJECT>
Logger StackBuffer<OBJECT>::LOGGER = Logger("StackBuffer<>", Level::DEBUG);

ENGINE_NAMESPACE_END