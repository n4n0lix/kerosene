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
#include "arraybuffertoken.h"

// TODO: Optimize the methods 'optimizeNext' and 'optimize'
// TODO: Merge RemoveOps and WriteOps to decrease the num of operations
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
class ArrayBuffer : public TransactionalBuffer<T>
{

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                        ArrayBuffer(uint32 objCapacity, uint32 objSize);

    using                               TransactionalBuffer<T>::commit;
    using                               TransactionalBuffer<T>::write;
    using                               TransactionalBuffer<T>::remove;
    using                               TransactionalBuffer<T>::num_objects;
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    virtual void                        commit_write(Vector<T> objects, shared_ptr<BufferToken> token);
    virtual void                        commit_remove(shared_ptr<BufferToken> token);

    virtual shared_ptr<BufferToken>     create_token(uint32 id);

    // Final-Implementation
    virtual void                        write(uint32 index, Vector<T> objects) = 0;
    virtual void                        remove(uint32 index, uint32 length) { };
    virtual void                        resize(uint32 oldCapacity, uint32 newCapacity) = 0;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            void                        optimize_free_ranges();
            bool                        _optimize_free_ranges();
            void                        merge_free_ranges(uint32 range1Id, uint32 range2Id);
            uint32                      get_free_range(uint32 length);

            void                        _resize(uint32 oldCapacity, uint32 newCapacity);

            uint32                      generate_range_id();

    Map<uint32, Range>    _freeRanges;
    Map<uint32, Range>    _usedRanges;

    uint32                      _nextUidRange;
    uint32                      _nextUidToken;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
ArrayBuffer<T>::ArrayBuffer(uint32 objSize, uint32 objCapacity) : TransactionalBuffer(objSize, objCapacity)
{
    // 0# Contract Pre

    // 1# Create initial range
    _nextUidRange = 0;
    auto initialRange = Range(0, atom_capacity());
    _freeRanges.put(generate_range_id(), initialRange);
    
    LOGGER.log(Level::DEBUG) << "CREATE [" << initialRange.index() << "," << initialRange.last_index() << "], OBJ SIZE: " << object_size() << endl;

    // X# Contract Post
    Ensures( !_freeRanges.empty() );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
void ArrayBuffer<T>::commit_write(Vector<T> objects, shared_ptr<BufferToken> aToken)
{
    auto token = static_pointer_cast<ArrayBufferToken>(aToken);

    // 0# Contract Pre
    Requires( objects.size() > 0 );
    Requires( aToken != nullptr );

    // 1# Get free range
    uint32_t size = (uint32_t)objects.size() * object_size();
    
    uint32 freeRangeId = get_free_range( size );
    Range freeRange    = _freeRanges.get( freeRangeId );

    _freeRanges.remove( freeRangeId );
    _usedRanges.put( freeRangeId, freeRange );

    // 2# Write
    LOGGER.log(Level::DEBUG) << "WRITE " << objects.size() << " AT [" << freeRange.index() << ", " << freeRange.last_index() << "]" << endl;
    write( freeRange.index(), std::move(objects) );

    // 3# Update and validate the token
    token->set_range_id( freeRangeId );
    token->set_atom_range( freeRange );
    token->set_object_size( object_size() );
    token->validate();

    // 4# Contract Post
    Ensures( token->valid() );
}

template<class T>
void ArrayBuffer<T>::commit_remove(shared_ptr<BufferToken> aToken)
{
    auto token = static_pointer_cast<ArrayBufferToken>(aToken);

    // 0# Contract Pre

    // 1# Get used range
    uint32 rangeId = token->range_id();

    if (!_usedRanges.contains(rangeId)) {
        LOGGER.log(Level::WARN) << "Attempting to remove unkown range with id: " << rangeId << endl;
        return;
    }

    Range range = _usedRanges.get(rangeId);

    // 2# Remove range
    remove(range.index(), range.length());

    _usedRanges.remove(rangeId);
    _freeRanges.put(rangeId, range);

    // 3# Invalidate token
    token->invalidate();

    // 4# Contract Post
    Ensures( !token->valid() );
}

template<class T>
inline shared_ptr<BufferToken> ArrayBuffer<T>::create_token(uint32 id)
{
    return make_shared<ArrayBufferToken>(id, this);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
void ArrayBuffer<T>::optimize_free_ranges() {
    bool hasChanged = false;

    do {
        hasChanged = _optimize_free_ranges();
    } while (hasChanged);
}

template<class T>
bool ArrayBuffer<T>::_optimize_free_ranges() {
    auto freeRanges = _freeRanges.as_vector();

    for (size_t i = 0; i < freeRanges.size(); i++) {
        for (size_t p = i + 1; p < freeRanges.size(); p++) {
            auto range1Id = freeRanges.at(i).first;
            auto range1 = freeRanges.at(i).second;

            auto range2Id = freeRanges.at(p).first;
            auto range2 = freeRanges.at(p).second;

            if (range1.index() + range1.length() == range2.index()) {
                merge_free_ranges(range1Id, range2Id);
                return true;
            }
            else if (range2.index() + range2.length() == range1.index()) {
                merge_free_ranges(range2Id, range1Id);
                return true;
            }
        }
    }

    return false;
}

template<class T>
void ArrayBuffer<T>::merge_free_ranges(uint32 range1Id, uint32 range2Id) {
    // 1# Guards
    if (!_freeRanges.contains(range1Id)) {
        return;
    }

    if (!_freeRanges.contains(range2Id)) {
        return;
    }

    Range range1 = _freeRanges.get(range1Id);
    Range range2 = _freeRanges.get(range2Id);

    if (range1.index() + range1.length() != range2.index()) {
        LOGGER.log(Level::WARN) << "Attempting to merge non-adjacent ranges with id: " << range1Id << ", " << range2Id << endl;
        return;
    }

    // 2# Create new range
    uint32 mergedRangeId = generate_range_id();
    auto mergedRange = Range(range1.index(), range1.length() + range2.length());

    // 3# Swap out ranges
    _freeRanges.remove(range1Id);
    _freeRanges.remove(range2Id);
    _freeRanges.put(mergedRangeId, mergedRange);
}

template<class T>
uint32 ArrayBuffer<T>::get_free_range(uint32 length) {
    // 1# Find a range with range.length >= length
    Nullable<uint32> optionalRangeId;

    for (auto pair : _freeRanges.as_vector()) {
        if (pair.second.length() >= length) {
            optionalRangeId = pair.first;
        }
    }

    // 2.1# If no range found: resize, search again
    if (optionalRangeId.is_null()) {
        _resize(atom_capacity(), atom_capacity() + length);

        for (auto pair : _freeRanges.as_vector()) {
            if (pair.second.length() >= length) {
                optionalRangeId = pair.first;
            }
        }

        if (optionalRangeId.is_null()) {
            throw std::logic_error("No free range found after resizing! Make sure resizing is implemented properly!");
        }
    }

    Range range = _freeRanges.get(optionalRangeId.get());

    // 2.2# If range is larger than needed, split
    if (range.length() > length) {
        uint32 newRange1Id = generate_range_id();
        auto newRange1 = Range(range.index(), length);

        uint32 newRange2Index = newRange1.index() + newRange1.length();
        uint32 newRange2Length = range.length() - length;
        auto newRange2 = Range(newRange2Index, newRange2Length);

        _freeRanges.remove(optionalRangeId.get());
        _freeRanges.put(newRange1Id, newRange1);
        _freeRanges.put(generate_range_id(), newRange2);

        return newRange1Id;
    }
    // 2.3# else return found range id
    else {
        return optionalRangeId.get();
    }
}

template<class T>
void ArrayBuffer<T>::_resize(uint32 oldAtomCapacity, uint32 newAtomCapacity) {
    resize(oldAtomCapacity, newAtomCapacity);

    set_atom_capacity(newAtomCapacity);

    auto additionalFreeRange = Range(oldAtomCapacity, newAtomCapacity - oldAtomCapacity);
    _freeRanges.put(generate_range_id(), additionalFreeRange);

    optimize_free_ranges();
}

template<class T>
uint32 ArrayBuffer<T>::generate_range_id() {
    return _nextUidRange++;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class OBJECT>
Logger ArrayBuffer<OBJECT>::LOGGER = Logger("ArrayBuffer<>", Level::OFF);

ENGINE_NAMESPACE_END