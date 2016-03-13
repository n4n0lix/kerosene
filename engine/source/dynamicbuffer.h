#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <algorithm>
        using std::max;

#include <vector>
        using std::vector;
        using std::find;
        using std::swap;

#include <functional>
        using std::function;

// Internal Includes
#include "_global.h"
#include "vectorutils.h"
#include "engineexception.h"
#include "logger.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Inner Classes                      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DynamicBufferToken {

public:
    DynamicBufferToken(void* buffer, uint32_t rangeUid) : buffer(buffer), rangeUid(rangeUid) {}

    /* The uid of the assoiated bufferrange. */
    uint32_t        rangeUid;

    /* The associated buffer. */
    void*           buffer;
};

class BufferRange {

public:
    BufferRange() : buffer(nullptr), rangeUid(0), index(0), length(0) {}
    BufferRange(void* buffer, uint32_t index, uint32_t length) : buffer(buffer), rangeUid(UID_COUNTER++), index(index), length(length) {}

    /* The associated buffer. */
    void* buffer;

    /* The unique id. */
    uint32_t rangeUid;

    /* The index where this range points into the buffer. */
    uint32_t index;

    /* The length of this range. */
    uint32_t length;

    bool operator==(const BufferRange& o) const { return rangeUid == o.rangeUid && buffer == o.buffer; };

private:
    static uint32_t UID_COUNTER;
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
   Base-class for dynamic write-only buffers. This manages free and used ranges so that the buffer
   is always used optimal. The buffersize growths as more space is needed.
 */
template<class T>
class DLL_PUBLIC DynamicBuffer
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    INLINE          DynamicBuffer<T>(uint32_t objectSize = 1, uint32_t initialCapcity = 10);

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    virtual void        write(uint32_t index, vector<T> objects) = 0;
    virtual void        remove(uint32_t index, uint32_t length) = 0;
    virtual void        resize(uint32_t oldCapacity, uint32_t newCapacity) = 0;


    INLINE uint32_t                       capacityObjects();
    INLINE uint32_t                       capacity();

    INLINE unique_ptr<DynamicBufferToken> write(vector<T> objects);
    INLINE void                           remove(unique_ptr<DynamicBufferToken> token);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    INLINE void            optimize();
    INLINE bool            optimizeNext();
    INLINE void            _resize(uint32_t oldCapacity, uint32_t newCapacity);
    INLINE void            mergeAdjacentFreeRanges(BufferRange range1, BufferRange range2);
    INLINE BufferRange     getFreeRange(uint32_t length);

    uint32_t    _objectSize;
    uint32_t    _capacity;

    vector<BufferRange> _freeRanges;
    vector<BufferRange> _usedRanges;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
DynamicBuffer<T>::DynamicBuffer(uint32_t objectSize, uint32_t initialCapcity) {
    _objectSize = objectSize;
    _capacity = _objectSize * initialCapcity;

    BufferRange initialRange = BufferRange(this, 0, capacity());
    _freeRanges.push_back(initialRange);

    std::cout << "output" << std::endl;
    LOGGER.log(DEBUG_RENDERING, std::ostringstream() << "Initial range [" << initialRange.index << "," << initialRange.length << ")");
}

template<class T>
uint32_t DynamicBuffer<T>::capacityObjects() {
    return _capacity / _objectSize;
}

template<class T>
uint32_t DynamicBuffer<T>::capacity() {
    return _capacity;
}

template<class T>
unique_ptr<DynamicBufferToken> DynamicBuffer<T>::write(vector<T> objects) {     
    // 1# Get free range
    uint32_t size = (uint32_t) objects.size() * _objectSize;
    BufferRange freeRange = getFreeRange(size);

    // 2# call write() for free range
    write(freeRange.index, objects);

    VectorUtils<BufferRange>::remove(_freeRanges, freeRange);
    VectorUtils<BufferRange>::add(_usedRanges, freeRange);

    // 3# Return token
    return make_unique<DynamicBufferToken>(this, freeRange.rangeUid);
}

template<class T>
void DynamicBuffer<T>::remove(unique_ptr<DynamicBufferToken> token) {
    // 1# Find range associated with 'token'
    BufferRange* range = nullptr;

    for (BufferRange aRange : _usedRanges) {
        if (aRange.rangeUid == token->rangeUid) {
            range = &aRange;
        }
    }

    if (range == nullptr) {
        throw EngineException("No BufferRange found for token (uid: " + token->rangeUid + ")!");
    }

    BufferRange usedRange = &range;
    range = nullptr;

    // 2# Remove buffer content
    remove(usedRange.index, usedRange.length);
    VectorUtils<BufferRange>::remove(_usedRanges, usedRange);
    VectorUtils<BufferRange>::add(_freeRanges, freeRange);

    // 3# Merge adjacent free ranges
    optimize();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
void DynamicBuffer<T>::optimize() {
    bool hasChanged = false;
    
    do {
        hasChanged = optimizeNext();
    } while (hasChanged);
}

template<class T>
bool DynamicBuffer<T>::optimizeNext() {
    for (size_t i = 0; i < _freeRanges.size(); i++) {
        for (size_t p = i + 1; p < _freeRanges.size(); p++) {
            BufferRange range1 = _freeRanges.at(i);
            BufferRange range2 = _freeRanges.at(p);

            if (range1.index + range1.length == range2.index) {
                mergeAdjacentFreeRanges(range1, range2);
                return true;
            }
            else if (range2.index + range2.length == range1.index) {
                mergeAdjacentFreeRanges(range2, range1);
                return true;
            }
        }
    }

    return false;
}

template<class T>
void DynamicBuffer<T>::_resize(uint32_t oldCapacity, uint32_t newCapacity) {
    resize(oldCapacity, newCapacity);

    _capacity = newCapacity;
    VectorUtils<BufferRange>::add(_freeRanges, BufferRange(this, oldCapacity, newCapacity - oldCapacity));
}

template<class T>
void DynamicBuffer<T>::mergeAdjacentFreeRanges(BufferRange range1, BufferRange range2) {
    // 1# Guards
    if (!VectorUtils<T>::contains(_freeRanges, range1)) {
        return;
    }

    if (!VectorUtils<T>::contains(_freeRanges, range2)) {
        return;
    }

    if (range1.index + range1.length != range2.index) {
        return;
    }

    // 2# Create new range
    BufferRange mergedRange = BufferRange(this, range1.index, range1.length + range2.length);

    // 3# Swap out ranges
    VectorUtils<T>::remove(_freeRanges, range1);
    VectorUtils<T>::remove(_freeRanges, range2);
    VectorUtils<T>::add(_freeRanges, mergedRange);
}

template<class T>
BufferRange DynamicBuffer<T>::getFreeRange(uint32_t length) {
    // 1# Find a range with range.length >= length
    BufferRange freeRange;
    bool foundRange = false;

    for (BufferRange aRange : _freeRanges) {
        if (aRange.length >= length) {
            freeRange = aRange;
            foundRange = true;
        }
    }

    // 2.1# If no range found, resize
    if (!foundRange) {
        _resize(capacity(), capacity() + length);

        for (BufferRange aRange : _freeRanges) {
            if (aRange.length >= length) {
                freeRange = aRange;
                foundRange = true;
            }
        }

        if (!foundRange) {
            throw EngineException("No free range found after resizing! Make sure resize(uint32_t, uint32_t) is implemented properly!");
        }
    }

    // 2.2# If range is larger than needed, split
    if (freeRange.length > length) {
        BufferRange oldRange = freeRange;
        BufferRange newRange1 = BufferRange(oldRange.buffer, oldRange.index, length);

        uint32_t newRange2Index  = newRange1.index + newRange1.length;
        uint32_t newRange2Length = oldRange.length - length;
        BufferRange newRange2 = BufferRange(oldRange.buffer, newRange2Index, newRange2Length);

        VectorUtils<BufferRange>::remove(_freeRanges, oldRange);
        VectorUtils<BufferRange>::add(_freeRanges, newRange1);
        VectorUtils<BufferRange>::add(_freeRanges, newRange2);

        freeRange = newRange1;
    }

    // 2.2# Return range
    return freeRange;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
Logger DynamicBuffer<T>::LOGGER = Logger("DynamicBuffer<>");

ENGINE_NAMESPACE_END
