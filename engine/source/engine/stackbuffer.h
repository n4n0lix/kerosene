#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <stdexcept>
#include <functional>

// Std-Extensions

// Internal Includes
#include "_global.h"
#include "owner.h"
#include "range.h"
#include "stackbuffertoken.h"
#include "logger.h"

#include "idgenerator.h"

// TODO: Optimize the methods 'optimizeNext' and 'optimize'
// TODO: Merge RemoveOps and WriteOps to decrease the num of operations
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
class StackBuffer
{

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                    StackBuffer(uint32 objSize, uint32 objCapacity);
                                    virtual ~StackBuffer() = default;

    uint32                                      object_size() const;
    uint32                                      object_capacity() const;
    uint32                                      atom_capacity() const;

    void                                        commit_write();
    void                                        commit_remove();

    uint32                                      num_objects();
    bool                                        contains(weak<StackBufferToken> token);

    weak<StackBufferToken>                      write(vector<T> objects);
    void                                        remove(weak<StackBufferToken> token);
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    void                            set_atom_capacity(uint32 newAtomCapacity);

    void                            commit_write(vector<T> objects, weak<StackBufferToken> commit_token);
    void                            commit_remove(weak<StackBufferToken> token);
        
    // Final-Implementation
    virtual void                    native_write(uint32 index, vector<T> objects) = 0;
    virtual void                    native_resize(uint32 oldCapacity, uint32 newCapacity) = 0;
    virtual void                    native_copy(uint32 srcIndex, uint32 destIndex, uint32 length) = 0;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            weak<StackBufferToken>    get_token_by_range_id(uint32 rangeId);


    Range                     _freeRange;
    map<uint32, Range>        _usedRanges; // TODO: Continue here, goal is to remove uid from within BufferRange

    uint32  _numObjects;
    uint32  _objectSize;
    uint32  _atomCapacity;

    map<weak<StackBufferToken>, vector<T>, weak_less<StackBufferToken>> _writeBucket;

    vector<weak<StackBufferToken>>    _removeBucket;
    vector<owner<StackBufferToken>>   _tokens;

    IDGen   _tokenIDGen;
    IDGen   _writeopIDGen;
    IDGen   _removeopIDGen;
    IDGen   _rangeIDGen;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
StackBuffer<T>::StackBuffer(uint32 objSize, uint32 objCapacity)
{
    _numObjects = 0;
    _atomCapacity = objSize * objCapacity;
    _objectSize = objSize;

    // 1# Create initial range
    _freeRange = Range(0, atom_capacity());
    LOGGER.log(Level::DEBUG) << "CREATE [" << _freeRange.index() << "," << _freeRange.length()-1 << "], OBJ SIZE: " << object_size()  << endl;

    // X# Contract Post
    Ensures( _freeRange.length() == atom_capacity() );
}

template<class T>
weak<StackBufferToken> StackBuffer<T>::write(vector<T> objects)
{
    // 1# Guards
    Requires(!objects.empty());

    // 2# Create token
    owner<StackBufferToken> token    = make_owner<StackBufferToken>( _tokenIDGen.new_id(), this);
    weak<StackBufferToken>  nonOwnerToken = token.get_non_owner();

    // 3# Store in write bucket
    _writeBucket.emplace( nonOwnerToken, std::move( objects ));
    _tokens.emplace_back( std::move( token ));

    // 4# Return token
    return nonOwnerToken;
}

template<class T>
void StackBuffer<T>::remove(weak<StackBufferToken> wToken)
{
    // 0# Contract pre
    Requires( wToken.ptr_is_valid() );
    Requires( wToken != nullptr);

    // 1# Check if token is invalid, and if it is remove corresponding writeops ...
    if ( !wToken->valid() ) {
        owner<StackBufferToken> oToken = extract_owner( _tokens, wToken );
        oToken.destroy();

        _writeBucket.erase( wToken );
        return;
    }

    // 2# Create RemoveOp for token
    _removeBucket.push_back( wToken );
}

template<class T>
void StackBuffer<T>::commit_write() {
    // 1# Do WriteOps
    for (auto pair = _writeBucket.begin(); pair != _writeBucket.end(); ++pair) {
        auto writeToken = pair->first;
        commit_write( std::move( pair->second ), writeToken );
        _numObjects += writeToken->object_range().length();
    }
    _writeBucket.clear();

    // X# Contract Post
    Ensures( _writeBucket.size() == 0 );
}

template<class T>
void StackBuffer<T>::commit_remove() {
    // 1# Do RemoveOps
    for (auto removeToken : _removeBucket) {
        commit_remove( removeToken );
        _numObjects -= removeToken->object_range().length();

        owner<StackBufferToken> token = extract_owner( _tokens, removeToken );
        token.destroy();
    }
    _removeBucket.clear();

    // X# Contract Post
    Ensures( _removeBucket.size() == 0 );
}

template<class T>
uint32 StackBuffer<T>::num_objects()
{
    return _numObjects;
}

template<class T>
bool StackBuffer<T>::contains(weak<StackBufferToken> token)
{
    return contains_owner( _tokens, token );
}

template <class T>
void StackBuffer<T>::set_atom_capacity(uint32 newAtomCapacity)
{
    _atomCapacity = newAtomCapacity;
}

template<class T>
uint32 StackBuffer<T>::object_size() const
{
    return _objectSize;
}

template<class T>
inline uint32 StackBuffer<T>::object_capacity() const
{
    return _atomCapacity / _objectSize;
}

template<class T>
inline uint32 StackBuffer<T>::atom_capacity() const
{
    return _atomCapacity;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
void StackBuffer<T>::commit_write(vector<T> objects, weak<StackBufferToken> token)
{
    // 0# Contract Pre
    Requires( objects.size() > 0 );
    Requires( token.ptr_is_valid() );
    Requires( token != nullptr );

    // 1# Check if freerange is large enough
    uint32 neededSize = (uint32_t)objects.size() * object_size();
    
    if (_freeRange.length() < neededSize) {
        // ... we need to grow the buffer
        uint32 oldAtomCapacity = atom_capacity();
        uint32 newAtomCapacity = oldAtomCapacity + neededSize;
        uint32 diffAtomCapacity = newAtomCapacity - oldAtomCapacity;

        native_resize(oldAtomCapacity, newAtomCapacity);
        LOGGER.log(Level::DEBUG) << "RESIZE FROM [" << oldAtomCapacity << "] TO [" << newAtomCapacity << "]" << endl;
        set_atom_capacity(newAtomCapacity);
        
        _freeRange = Range(_freeRange.index(), 
                           _freeRange.index() + diffAtomCapacity);
        LOGGER.log(Level::DEBUG) << "FREE IS [" << _freeRange.index() << ", " << _freeRange.last_index() << "]" << endl;
    }

    // 2# Split of range of 'free range'
    uint32 usedRangeId = _rangeIDGen.new_id();
    Range usedRange = Range(_freeRange.index(), neededSize);
    _freeRange = Range(usedRange.index() + usedRange.length(), _freeRange.length() - usedRange.length());

    // 2#  Write
    LOGGER.log(Level::DEBUG) << "WRITE " << objects.size() << " AT [" << usedRange.index() << ", " << usedRange.index() + neededSize - 1 << "]" << endl;
    LOGGER.log(Level::DEBUG) << "FREE IS [" << _freeRange.index() << ", " << _freeRange.last_index() << "]" << endl;

    native_write(usedRange.index(), std::move(objects));

    _usedRanges[usedRangeId] = usedRange;

    // 3# Update and validate the token
    token->set_range_id(usedRangeId);
    token->set_atom_range(usedRange);
    token->set_object_size(object_size());
    token->validate();

    // X# Contract Post
    Ensures( token->valid() );
}

template<class T>
void StackBuffer<T>::commit_remove(weak<StackBufferToken> token)
{
    Requires( token.ptr_is_valid() );
    Requires( token != nullptr );

    // 1# Get used range
    uint32 rangeId = token->range_id();

    if ( _usedRanges.count( rangeId ) == 0 ) {
        LOGGER.log(Level::DEBUG) << "Attempting to remove unkown range with id: " << rangeId << "\n";
        return;
    }
    
    Range range = _usedRanges[rangeId];

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
    native_copy(copySourceFirst, copyDestFirst, copySourceLength);
    LOGGER.log(Level::DEBUG) << "COPY [" << copySourceFirst << ", " << copySourceLast << "] TO [" << copyDestFirst << ", " << copyDestLast << "]" << endl;

    _usedRanges.erase(rangeId);
    _freeRange = Range(freeRangeFirst, freeRangeLength);

    // 2.4# Update all ranges
    for (auto pair = _usedRanges.begin(); pair != _usedRanges.end(); ++pair) {
        uint32 id = pair->first;
        Range  range = pair->second;

        // Determine if range is affected by deletion
        if (range.index() > delRangeLast) {
            // Update Range
            range.move( moveDistance );

            _usedRanges[ id ] = range;

            // Update Token
            auto token = get_token_by_range_id( id );
            token->set_atom_range( range );

            LOGGER.log( Level::DEBUG ) << "UPDATE TOKEN" << endl;
        }
    }

    // 3# Invalidate token
    token->invalidate();
}

template<class T>
weak<StackBufferToken> StackBuffer<T>::get_token_by_range_id(uint32 rangeId)
{
    // 1# Search in tokens
    for (auto token = _tokens.begin(); token != _tokens.end(); ++token) {
        if (token->get()->range_id() == rangeId) {
            return token->get_non_owner();
        }
    }

    return nullptr;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
Logger StackBuffer<T>::LOGGER = Logger("StackBuffer<>", Level::WARN);

ENGINE_NAMESPACE_END