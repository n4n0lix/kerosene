//#pragma once
//
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*                        Includes                        */
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//// Std-Includes
//
//// Internal Includes
//#include "_global.h"
//#include "vectorutils.h"
//#include "engineexception.h"
//#include "logger.h"
//#include "writeonlybuffer.h"
//#include "dynamicbufferrange.h"
//
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*                     Inner Classes                      */
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//ENGINE_NAMESPACE_BEGIN
//
//template<class T>
//class DynamicBuffer;
//
//class DynamicBufferToken : public WOB_Token {
//    template <class T> friend class DynamicBuffer;
//public:
//    DynamicBufferToken(uint32 atomIndex, uint32 atomLength, uint32 objSize, void* buffer, uint32 rangeUid) 
//        : WOB_Token(atomIndex,atomLength, objSize), buffer(buffer), rangeUid(rangeUid) {}
//
//private:
//    /* The uid of the assoiated bufferrange. */
//    uint32          rangeUid;
//
//    /* The associated buffer. */
//    void*           buffer;
//};
//
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*                         Class                          */
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*
//   Base-class for dynamic write-only buffers. This manages free and used ranges so that the buffer
//   is always used optimal. The buffersize growths as more space is needed.
// */
//template<class T>
//class DLL_PUBLIC DynamicBuffer : public WriteOnlyBuffer<T>
//{
//
//public:
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//    /*                        Public                          */
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//                DynamicBuffer<T>(uint32 objectSize = 1, uint32 initialCapcity = 10);
//
//protected:
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//    /*                       Protected                        */
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//    virtual void        write(uint32 index, vector<T> objects) = 0;
//    virtual void        remove(uint32 index, uint32 length) = 0;
//    virtual void        resize(uint32 oldCapacity, uint32 newCapacity) = 0;
//
//    virtual shared_ptr<WriteOnlyBufferToken> write(vector<T> objects);
//    virtual void                             remove(shared_ptr<WriteOnlyBufferToken> token);
//
//private:
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//    /*                        Private                         */
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//    void                 optimize();
//    bool                 optimizeNext();
//    void                 _resize(uint32 oldCapacity, uint32 newCapacity);
//    void                 mergeAdjacentFreeRanges(DynamicBuffer_Range range1, DynamicBuffer_Range range2);
//    DynamicBuffer_Range  getFreeRange(uint32_t length);
//
//    uint32    _uid;
//    vector<DynamicBuffer_Range> _freeRanges;
//    vector<DynamicBuffer_Range> _usedRanges;
//
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//    /*                     Private Static                     */
//    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//    static Logger LOGGER;
//    static atomic<uint32_t> NEXT_UID;
//};
//
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*                        Public                          */
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//template<class T>
//DynamicBuffer<T>::DynamicBuffer(uint32_t objectSize, uint32_t initialCapacity)
//    : Buffer(objectSize, initialCapacity),
//      _freeRanges(vector<DynamicBuffer_Range>()),
//      _usedRanges(vector<DynamicBuffer_Range>()),
//      _uid(NEXT_UID++)
//{
//    auto initialRange = DynamicBuffer_Range(this, 0, atom_capacity());
//    _freeRanges.push_back(initialRange);
//
//    LOGGER.log(Level::DEBUG, _uid) << "CREATE [" << initialRange.index << "," << initialRange.length-1 << "], OBJ SIZE: " << object_size()  << endl;
//}
//
//template<class T>
//shared_ptr<WriteOnlyBufferToken> DynamicBuffer<T>::write(vector<T> objects) {
//    // 1# Get free range
//    uint32_t size = (uint32_t) objects.size() * object_size();
//    auto freeRange = getFreeRange(size);
//
//    // 2# call write() for free range
//    write(freeRange.index, objects);
//    VectorUtils<DynamicBuffer_Range>::remove(_freeRanges, freeRange);
//    VectorUtils<DynamicBuffer_Range>::add(_usedRanges, freeRange);
//    
//    LOGGER.log(Level::DEBUG, _uid) << "WRITE " << objects.size() << " AT [" << freeRange.index << ", " << freeRange.index + size-1 << "]" << endl;
//
//    // 3# Return token
//    uint32 atomIndex = freeRange.index;
//    uint32 atomLength = freeRange.length;
//    shared_ptr<DynamicBufferToken> token = make_shared<DynamicBufferToken>(atomIndex, atomLength, object_size(), this, freeRange.rangeUid);
//    return std::static_pointer_cast<BufferToken>(token);
//}
//
//template<class T>
//void DynamicBuffer<T>::remove(shared_ptr<BufferToken> bufferToken) {
//    // 1# Find range associated with 'token'
//    shared_ptr<DynamicBufferToken> token = std::static_pointer_cast<DynamicBufferToken>(bufferToken);
//    DynamicBuffer_Range* range = nullptr;
//
//    for (auto aRange : _usedRanges) {
//        if (aRange.rangeUid == token->rangeUid) {
//            range = &aRange;
//        }
//    }
//
//    if (range == nullptr) {
//        LOGGER.log(Level::WARN) << "Remove called with invalid token!");
//        return;
//    }
//
//    DynamicBuffer_Range usedRange = *range;
//    range = nullptr;
//
//    // 2# Remove buffer content
//    LOGGER.log(Level::DEBUG, _uid) << "REMOVE [" << usedRange.index << ", " << usedRange.index + usedRange.length - 1 << "]" << endl;
//    remove(usedRange.index, usedRange.length);
//    VectorUtils<DynamicBuffer_Range>::remove(_usedRanges, usedRange);
//    VectorUtils<DynamicBuffer_Range>::add(_freeRanges, usedRange);
//
//    // 3# Merge adjacent free ranges
//    optimize();
//}
//
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*                       Protected                        */
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*                        Private                         */
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//template<class T>
//void DynamicBuffer<T>::optimize() {
//    bool hasChanged = false;
//    
//    do {
//        hasChanged = optimizeNext();
//    } while (hasChanged);
//}
//
//template<class T>
//bool DynamicBuffer<T>::optimizeNext() {
//    for (size_t i = 0; i < _freeRanges.size(); i++) {
//        for (size_t p = i + 1; p < _freeRanges.size(); p++) {
//            auto range1 = _freeRanges.at(i);
//            auto range2 = _freeRanges.at(p);
//
//            if (range1.index + range1.length == range2.index) {
//                mergeAdjacentFreeRanges(range1, range2);
//                return true;
//            }
//            else if (range2.index + range2.length == range1.index) {
//                mergeAdjacentFreeRanges(range2, range1);
//                return true;
//            }
//        }
//    }
//
//    return false;
//}
//
//template<class T>
//void DynamicBuffer<T>::_resize(uint32 oldAtomCapacity, uint32 newAtomCapacity) {
//    resize(oldAtomCapacity, newAtomCapacity);
//
//    set_atom_capacity(newAtomCapacity);
//    VectorUtils<DynamicBuffer_Range>::add(_freeRanges, DynamicBuffer_Range(this, oldAtomCapacity, newAtomCapacity - oldAtomCapacity));
//
//    optimize();
//}
//
//template<class T>
//void DynamicBuffer<T>::mergeAdjacentFreeRanges(DynamicBuffer_Range range1, DynamicBuffer_Range range2) {
//    // 1# Guards
//    if (!VectorUtils<DynamicBuffer_Range>::contains(_freeRanges, range1)) {
//        return;
//    }
//
//    if (!VectorUtils<DynamicBuffer_Range>::contains(_freeRanges, range2)) {
//        return;
//    }
//
//    if (range1.index + range1.length != range2.index) {
//        return;
//    }
//
//    // 2# Create new range
//    auto mergedRange = DynamicBuffer_Range(this, range1.index, range1.length + range2.length);
//
//    // 3# Swap out ranges
//    VectorUtils<DynamicBuffer_Range>::remove(_freeRanges, range1);
//    VectorUtils<DynamicBuffer_Range>::remove(_freeRanges, range2);
//    VectorUtils<DynamicBuffer_Range>::add(_freeRanges, mergedRange);
//}
//
//template<class T>
//DynamicBuffer_Range DynamicBuffer<T>::getFreeRange(uint32 length) {
//    // 1# Find a range with range.length >= length
//    DynamicBuffer_Range freeRange;
//    bool foundRange = false;
//
//    for (auto aRange : _freeRanges) {
//        if (aRange.length >= length) {
//            freeRange = aRange;
//            foundRange = true;
//        }
//    }
//
//    // 2.1# If no range found, resize
//    if (!foundRange) {
//        _resize(atom_capacity(), atom_capacity() + length);
//
//        for (auto aRange : _freeRanges) {
//            if (aRange.length >= length) {
//                freeRange = aRange;
//                foundRange = true;
//            }
//        }
//
//        if (!foundRange) {
//            throw EngineException("No free range found after resizing! Make sure resize(uint32_t, uint32_t) is implemented properly!");
//        }
//    }
//
//    // 2.2# If range is larger than needed, split
//    if (freeRange.length > length) {
//        auto oldRange = freeRange;
//        auto newRange1 = DynamicBuffer_Range(oldRange.buffer, oldRange.index, length);
//
//        uint32_t newRange2Index  = newRange1.index + newRange1.length;
//        uint32_t newRange2Length = oldRange.length - length;
//        auto newRange2 = DynamicBuffer_Range(oldRange.buffer, newRange2Index, newRange2Length);
//
//        VectorUtils<DynamicBuffer_Range>::remove(_freeRanges, oldRange);
//        VectorUtils<DynamicBuffer_Range>::add(_freeRanges, newRange1);
//        VectorUtils<DynamicBuffer_Range>::add(_freeRanges, newRange2);
//
//        freeRange = newRange1;
//    }
//
//    // 2.2# Return range
//    return freeRange;
//}
//
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
///*                     Private Static                     */
///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//template<class T>
//Logger DynamicBuffer<T>::LOGGER = Logger("DynamicBuffer<>", Level::DEBUG);
//
//template<class T>
//atomic<uint32> DynamicBuffer<T>::NEXT_UID = 0;
//
//ENGINE_NAMESPACE_END
