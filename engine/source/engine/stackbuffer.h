#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <stdexcept>
#include <functional>

// Internal Includes
#include "_global.h"
#include "vector.h"

#include "buffer.h"
#include "bufferrange.h"

#include "transactionalbuffer.h"

#include "tb_token.h"
#include "tb_writeop.h"
#include "tb_removeop.h"

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

    using                               TransactionalBuffer<T>::commit;
    using                               TransactionalBuffer<T>::write;
    using                               TransactionalBuffer<T>::remove;
    using                               TransactionalBuffer<T>::num_objects;
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    virtual void                        commit_write(shared_ptr<vector<T>> objects, shared_ptr<TB_Token> commit_token);
    virtual void                        commit_remove(shared_ptr<TB_Token> token);

    using                               TransactionalBuffer::create_token;

    // Final-Implementation
    virtual void                        write(uint32 index, shared_ptr<vector<T>> objects) = 0;
    virtual void                        remove(uint32 index, uint32 length) { };
    virtual void                        resize(uint32 oldCapacity, uint32 newCapacity) = 0;
    virtual void                        copy(uint32 srcIndex, uint32 destIndex, uint32 length) = 0;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            void                     _write(shared_ptr<TB_WriteOp<T>> writeOp);
            void                     _remove(shared_ptr<TB_RemoveOp> writeOp);

            uint32                   generateRangeId();

    BufferRange                     _freeRange;
    Vector<BufferRange>             _usedRanges;

    uint32                  _nextUidRange;

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
    _nextUidRange = BufferRange::FIRST_ID;

    // 1# Create initial range
    _freeRange = BufferRange(generateRangeId(), this, 0, atom_capacity());
    LOGGER.log(Level::DEBUG) << "CREATE [" << _freeRange.index() << "," << _freeRange.length()-1 << "], OBJ SIZE: " << object_size()  << endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
void StackBuffer<T>::commit_write(shared_ptr<vector<T>> objects, shared_ptr<TB_Token> token)
{
    // 1# Check if freerange is large enough
    uint32_t neededSize = (uint32_t)objects->size() * object_size();
    
    if (_freeRange.length() < neededSize) {
        // ... we need to grow the buffer
        uint32 oldAtomCapacity = atom_capacity();
        uint32 newAtomCapacity = oldAtomCapacity + neededSize;

        resize(oldAtomCapacity, newAtomCapacity);
        LOGGER.log(Level::DEBUG) << "RESIZE FROM [" << oldAtomCapacity << "] TO [" << newAtomCapacity << "]" << endl;
        set_atom_capacity(newAtomCapacity);
        
        _freeRange = BufferRange(_freeRange.id(), 
                                 this, 
                                 _freeRange.index(), 
                                 _freeRange.index() + (newAtomCapacity - oldAtomCapacity));
        LOGGER.log(Level::DEBUG) << "FREE IS [" << _freeRange.index() << ", " << _freeRange.last_index() << "]" << endl;
    }

    // 2# Split of range of 'free range'
    BufferRange usedRange = BufferRange(generateRangeId(), this, _freeRange.index(), neededSize);
    _freeRange = BufferRange(_freeRange.id(), this, usedRange.index() + usedRange.length(), _freeRange.length() - usedRange.length());

    // 2#  Write
    write(usedRange.index(), objects);
    LOGGER.log(Level::DEBUG) << "WRITE " << objects->size() << " AT [" << usedRange.index() << ", " << usedRange.index() + neededSize - 1 << "]" << endl;
    LOGGER.log(Level::DEBUG) << "FREE IS [" << _freeRange.index() << ", " << _freeRange.last_index() << "]" << endl;

    _usedRanges.add(usedRange);

    // 3# Update and validate the token
    token->set_range_id(usedRange.id());
    token->set_data(usedRange.index(), usedRange.length(), object_size());
    token->validate();
}

template<class OBJECT>
void StackBuffer<OBJECT>::commit_remove(shared_ptr<TB_Token> token)
{
    // 1# Get used range
    uint32 rangeId = token->range_id();
    Vector<BufferRange> ranges;

    _usedRanges.collect(ranges, [&](BufferRange& range) -> bool { return range.id() == rangeId; });

    // 2# Remove range
    for (BufferRange range : ranges) {
        uint32 delRangeFirst = range.index();
        uint32 delRangeLast = range.index() + range.length();
        uint32 delRangeLength = range.length();

        uint32 srcCopyRangeFirst = delRangeLast + 1;
        uint32 srcCopyRangeLast = _freeRange.index()-1;
        uint32 copyRangeLength = (srcCopyRangeLast - srcCopyRangeFirst) + 1;

        uint32 destCopyRangeFirst = delRangeFirst;
        uint32 destCopyRangeLast = delRangeFirst + copyRangeLength;

        uint32 freeRangeFirst = destCopyRangeLast + 1;
        uint32 freeRangeLast = atom_capacity();
        uint32 freeRangeLength = (freeRangeLast - freeRangeFirst) + 1;

        uint32 moveDistance = srcCopyRangeFirst - destCopyRangeFirst;

        copy(srcCopyRangeFirst, destCopyRangeFirst, copyRangeLength);
        LOGGER.log(Level::DEBUG) << "COPY [" << srcCopyRangeFirst << ", " << srcCopyRangeLast << "] TO [" << destCopyRangeFirst << ", " << destCopyRangeLast << "]" << endl;

        remove(freeRangeFirst, freeRangeLength);
        LOGGER.log(Level::DEBUG) << "REMOVE [" << freeRangeFirst << ", " << (freeRangeFirst + freeRangeLength)-1 << "]" << endl;

        _usedRanges.remove(range);
        _freeRange = BufferRange(_freeRange.id(), this, freeRangeFirst, freeRangeLength);

        // 2.2# Update all tokens
        for (auto aToken : get_active_tokens()) {
            if (aToken->atom_index() > delRangeLast) {
                uint32 oldTokenIndex = aToken->atom_index();
                aToken->set_data(aToken->atom_index() - moveDistance, aToken->atom_length(), aToken->object_size());
                LOGGER.log(Level::DEBUG) << "UPDATE TOKEN [" << oldTokenIndex << ", " << (oldTokenIndex + aToken->atom_length()) - 1 << "] TO [" << aToken->atom_index() << ", " << (aToken->atom_index() + aToken->atom_length()) - 1 << "]" << endl;
            }
        }
    }

    // 3# Invalidate token
    token->invalidate();
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