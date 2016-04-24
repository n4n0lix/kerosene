#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <stdexcept>
#include <functional>

// Internal Includes
#include "_global.h"
#include "writeonlybuffer.h"
#include "vectorutils.h"

#include "tb_range.h"
#include "tb_token.h"
#include "tb_writeop.h"
#include "tb_removeop.h"

// TODO: Optimize the method 'optimizeNext' and 'optimize'
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class OBJECT>
class TransactionalBuffer : public WriteOnlyBuffer<OBJECT>
{

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            TransactionalBuffer(uint32 objCapacity, uint32 objSize);


            void                     commit();

    virtual shared_ptr<WOB_Token>    write(shared_ptr<vector<OBJECT>> objects);
    virtual void                     remove(shared_ptr<WOB_Token> token);
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    virtual void                     write(uint32 index, shared_ptr<vector<OBJECT>> objects) = 0;
    virtual void                     remove(uint32 index, uint32 length) = 0;
    virtual void                     resize(uint32 oldCapacity, uint32 newCapacity) = 0;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            void                     optimize();
            bool                     optimizeNext();
            void                     mergeAdjacentFreeRanges(TB_Range range1, TB_Range range2);
            TB_Range                 getFreeRange(uint32 length);
            
            void                     _write(shared_ptr<TB_WriteOp<OBJECT>> writeOp);
            void                     _remove(shared_ptr<TB_RemoveOp> writeOp);
            void                     _resize(uint32 oldCapacity, uint32 newCapacity);

            uint32                   generateRangeId();
            uint32                   generateTokenId();
            uint32                   generateWriteOpId();
            uint32                   generateRemoveOpId();

    vector<TB_Range>        _freeRanges;
    vector<TB_Range>        _reservedRanges;
    vector<TB_Range>        _usedRanges;

    vector<shared_ptr<TB_WriteOp<OBJECT>>>  _writeBucket;
    vector<shared_ptr<TB_RemoveOp>>         _removeBucket;

    uint32                  _nextUidRange;
    uint32                  _nextUidToken;
    uint32                  _nextUidWriteOp;
    uint32                  _nextUidRemoveOp;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class OBJECT>
TransactionalBuffer<OBJECT>::TransactionalBuffer(uint32 objSize, uint32 objCapacity) : WriteOnlyBuffer(objSize, objCapacity)
{
    _nextUidRange    = TB_Range::FIRST_ID;
    _nextUidToken    = TB_Token::FIRST_UID;
    _nextUidWriteOp  = TB_WriteOp<OBJECT>::FIRST_UID;
    _nextUidRemoveOp = TB_RemoveOp::FIRST_UID;


    auto initialRange = TB_Range(generateRangeId(), this, 0, atom_capacity());
    _freeRanges.push_back(initialRange);
    
    LOGGER.log(Level::DEBUG) << "CREATE [" << initialRange.index() << "," << initialRange.length()-1 << "], OBJ SIZE: " << object_size()  << endl;
}

template<class OBJECT>
shared_ptr<WOB_Token> TransactionalBuffer<OBJECT>::write(shared_ptr<vector<OBJECT>> objects)
{
    // 1# Create token
    shared_ptr<TB_Token> token = make_shared<TB_Token>(generateTokenId(), this);

    // 2# Store in write bucket
    _writeBucket.push_back(make_shared<TB_WriteOp<OBJECT>>(generateWriteOpId(), token, objects));

    // 3# Return token
    return dynamic_pointer_cast<WOB_Token>(token);
}

template<class OBJECT>
void TransactionalBuffer<OBJECT>::remove(shared_ptr<WOB_Token> woToken)
{
    // 1# Only accept TB_Token
    shared_ptr<TB_Token> token;

    if (!(token = static_pointer_cast<TB_Token>(woToken))) {
        LOGGER.log(Level::WARN) << "Invalid token received, not of class TB_Token!" << endl;
        return;
    }

    // 2# Check if token has been assigned a range ...
    if (token->range_id() == TB_Range::NULL_ID) {
        // ... and if not, remove possible WriteOps with this token
        //std::function<bool(shared_ptr<TB_WriteOp<OBJECT>>)> delFunc = ;
        VectorUtils<shared_ptr<TB_WriteOp<OBJECT>>>::remove(_writeBucket, [&](shared_ptr<TB_WriteOp<OBJECT>> op) -> bool { return op->token() == token; });
        return;
    }

    // 3# Create RemoveOp for token
    VectorUtils<shared_ptr<TB_RemoveOp>>::add(_removeBucket, make_shared<TB_RemoveOp>(generateRemoveOpId(), token));
}

template<class OBJECT>
void TransactionalBuffer<OBJECT>::commit() {
    // 1# Do RemoveOps
    for (auto removeOp : _removeBucket) {
        _remove(removeOp);
    }
    _removeBucket.clear();

    // 2# Do WriteOps
    for (auto writeOp : _writeBucket) {
        _write(writeOp);
    }
    _writeBucket.clear();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class OBJECT>
void TransactionalBuffer<OBJECT>::optimize() {
    bool hasChanged = false;

    do {
        hasChanged = optimizeNext();
    } while (hasChanged);
}

template<class OBJECT>
bool TransactionalBuffer<OBJECT>::optimizeNext() {
    for (size_t i = 0; i < _freeRanges.size(); i++) {
        for (size_t p = i + 1; p < _freeRanges.size(); p++) {
            auto range1 = _freeRanges.at(i);
            auto range2 = _freeRanges.at(p);

            if (range1.index() + range1.length() == range2.index()) {
                mergeAdjacentFreeRanges(range1, range2);
                return true;
            }
            else if (range2.index() + range2.length() == range1.index()) {
                mergeAdjacentFreeRanges(range2, range1);
                return true;
            }
        }
    }

    return false;
}

template<class OBJECT>
void TransactionalBuffer<OBJECT>::mergeAdjacentFreeRanges(TB_Range range1, TB_Range range2) {
    // 1# Guards
    if (!VectorUtils<TB_Range>::contains(_freeRanges, range1)) {
        return;
    }

    if (!VectorUtils<TB_Range>::contains(_freeRanges, range2)) {
        return;
    }

    if (range1.index() + range1.length() != range2.index()) {
        return;
    }

    // 2# Create new range
    auto mergedRange = TB_Range(generateRangeId(), this, range1.index(), range1.length() + range2.length());

    // 3# Swap out ranges
    VectorUtils<TB_Range>::remove(_freeRanges, range1);
    VectorUtils<TB_Range>::remove(_freeRanges, range2);
    VectorUtils<TB_Range>::add(_freeRanges, mergedRange);
}

template<class OBJECT>
TB_Range TransactionalBuffer<OBJECT>::getFreeRange(uint32 length) {
    // 1# Find a range with range.length >= length
    TB_Range freeRange;
    bool foundRange = false;

    for (auto aRange : _freeRanges) {
        if (aRange.length() >= length) {
            freeRange = aRange;
            foundRange = true;
        }
    }

    // 2.1# If no range found, resize
    if (!foundRange) {
        _resize(atom_capacity(), atom_capacity() + length);

        for (auto aRange : _freeRanges) {
            if (aRange.length() >= length) {
                freeRange = aRange;
                foundRange = true;
            }
        }

        if (!foundRange) {
            throw std::logic_error("No free range found after resizing! Make sure resizing is implemented properly!");
        }
    }

    // 2.2# If range is larger than needed, split
    if (freeRange.length() > length) {
        auto oldRange = freeRange;
        auto newRange1 = TB_Range(generateRangeId(), this, oldRange.index(), length);

        uint32_t newRange2Index = newRange1.index() + newRange1.length();
        uint32_t newRange2Length = oldRange.length() - length;
        auto newRange2 = TB_Range(generateRangeId(), this, newRange2Index, newRange2Length);

        VectorUtils<TB_Range>::remove(_freeRanges, oldRange);
        VectorUtils<TB_Range>::add(_freeRanges, newRange1);
        VectorUtils<TB_Range>::add(_freeRanges, newRange2);

        freeRange = newRange1;
    }

    // 2.2# Return range
    return freeRange;
}

template<class OBJECT>
void TransactionalBuffer<OBJECT>::_write(shared_ptr<TB_WriteOp<OBJECT>> writeOp)
{
    shared_ptr<vector<OBJECT>> objects = writeOp->objects();

    // 1# Get free range
    uint32_t size = (uint32_t)objects->size() * object_size();
    TB_Range freeRange = getFreeRange(size);

    VectorUtils<TB_Range>::remove(_freeRanges, freeRange);
    VectorUtils<TB_Range>::add(_usedRanges, freeRange);

    // 2#  Write
    write(freeRange.index(), objects);
    LOGGER.log(Level::DEBUG) << "WRITE " << objects->size() << " AT [" << freeRange.index() << ", " << freeRange.index() + size - 1 << "]" << endl;

    // 3# Update and validate the token
    auto token = writeOp->token();
    token->set_range_id(freeRange.id());
    token->set_data(freeRange.index(), freeRange.length(), object_size());
    token->validate();
}

template<class OBJECT>
void TransactionalBuffer<OBJECT>::_remove(shared_ptr<TB_RemoveOp> removeOp)
{
    // 1# Get used range
    uint32 rangeId = removeOp->token()->range_id();
    vector<TB_Range> ranges;

    VectorUtils<TB_Range>::forAll(_usedRanges, [&](TB_Range& range) -> void {
                                                                                if (range.id() == rangeId) {
                                                                                    ranges.push_back(range);
                                                                                }
                                                                            });

    // 2# Remove range
    for (TB_Range range : ranges) {
        remove(range.index(), range.length());
        VectorUtils<TB_Range>::remove(_usedRanges, range);
        VectorUtils<TB_Range>::add(_freeRanges, range);
    }

    // 3# Invalidate token
    removeOp->token()->invalidate();
}

template<class T>
void TransactionalBuffer<T>::_resize(uint32 oldAtomCapacity, uint32 newAtomCapacity) {
    resize(oldAtomCapacity, newAtomCapacity);

    set_atom_capacity(newAtomCapacity);
    VectorUtils<TB_Range>::add(_freeRanges, TB_Range(generateRangeId(), this, oldAtomCapacity, newAtomCapacity - oldAtomCapacity));

    optimize();
}

template<class T>
uint32 TransactionalBuffer<T>::generateRangeId() {
    return _nextUidRange++;
}

template<class T>
uint32 TransactionalBuffer<T>::generateTokenId() {
    return _nextUidToken++;
}

template<class T>
uint32 TransactionalBuffer<T>::generateWriteOpId() {
    return _nextUidWriteOp++;
}

template<class T>
uint32 TransactionalBuffer<T>::generateRemoveOpId() {
    return _nextUidRemoveOp++;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class OBJECT>
Logger TransactionalBuffer<OBJECT>::LOGGER = Logger("TransactionalBuffer<>", Level::DEBUG);

ENGINE_NAMESPACE_END