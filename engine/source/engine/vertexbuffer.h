#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <ostream>
#include <stdexcept>
#include <functional>

// Other Includes

// Std-Extensions

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "_renderdefs.h"

#include "idgen.h"
#include "logger.h"

#include "range.h"

#include "vertexbuffertoken.h"

#include "vertexlayout.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
class VertexBuffer
{
public:
                VertexBuffer(VertexLayout layout, uint32 initCapacity);
                ~VertexBuffer();

            GLuint                      get_id() const;
            uint32                      object_size() const;
            uint32                      object_capacity() const;
            uint32                      atom_capacity() const;

            weak<VertexBufferToken>     add_vertices( std::vector<T> vertices);
            void                        remove_vertices(weak<VertexBufferToken> token);
            void                        clear();

            void                        commit_write();
            void                        commit_remove();

    virtual uint32                      num_vertices() const;
            bool                        contains(weak<VertexBufferToken> token) const;

protected:
            void                        native_remove_at(uint32 index, uint32 length);
            void                        native_resize(uint32 oldCapacity, uint32 newCapacity);
            
            void                        commit_write( std::vector<T> objects, weak<VertexBufferToken> token);
            void                        commit_remove(weak<VertexBufferToken> token);

            void                        native_write_at(uint32 index, std::vector<float> data);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                        optimize_free_ranges();
    bool                        _optimize_free_ranges();
    void                        merge_free_ranges(uint32 range1Id, uint32 range2Id);
    uint32                      get_free_range(uint32 length);

    void                        resize(uint32 oldCapacity, uint32 newCapacity);

    uint32                _vboId;
    uint32                _numVertices;
    uint32                _atomCapacity;

    VertexLayout          _layout;

    map<uint32, Range>    _freeRanges;
    map<uint32, Range>    _usedRanges;

    map<weak<VertexBufferToken>, std::vector<T>, weak_less<VertexBufferToken>> _writeBucket;

    std::vector<weak<VertexBufferToken>>      _removeBucket;
    std::vector<owner<VertexBufferToken>>      _tokens;

    IDGen                 _rangeIDGen;
    IDGen                 _tokenIDGen;
    IDGen                 _writeOpIDGen;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLuint      createVBO(uint32 capacityBytes);

static Logger LOGGER;

};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
VertexBuffer<T>::VertexBuffer(VertexLayout layout, uint32 initCapacity) : _layout(layout), _numVertices(0), _atomCapacity(layout.bytesize() * initCapacity) {
    // 1# Buffer Mgmt
    auto initialRange = Range(0, _atomCapacity);
    _freeRanges[ _rangeIDGen.new_id() ] = initialRange;
    LOGGER.log(Level::DEBUG) << "CREATE [" << initialRange.index() << "," << initialRange.last_index() << "], OBJ SIZE: " << object_size() << "\n";

    // 2# OpenGL
    _vboId = createVBO(_atomCapacity);
    LOGGER.log(Level::DEBUG, _vboId) << "CREATE\n";

    // X# Contract Post
    Ensures(!_freeRanges.empty());
}

template<class T>
VertexBuffer<T>::~VertexBuffer()
{
    LOGGER.log(Level::DEBUG, _vboId) << "DELETE\n";
    glDeleteBuffers(1, &_vboId);
}

template<class T>
GLuint VertexBuffer<T>::get_id() const
{
    return _vboId;
}

template<class T>
weak<VertexBufferToken> VertexBuffer<T>::add_vertices( std::vector<T> vertices)
{
    LOGGER.log(Level::DEBUG, _vboId) << "ADD " << vertices.size() << " vertices\n";
    // 1# Guards
    Requires( vertices.size() > 0 );

    // 2# Create token
    owner<VertexBufferToken> token = make_owner<VertexBufferToken>(_tokenIDGen.new_id(), this);
    weak<VertexBufferToken> nonOwner = token.get_non_owner();

    // 3# Store in write bucket
    _writeBucket.emplace( nonOwner, std::move( vertices ));
    _tokens.emplace_back( std::move( token ));

    // 4# Return token
    return nonOwner;
}

template<class T>
void VertexBuffer<T>::remove_vertices(weak<VertexBufferToken> wToken)
{
    // 0# Contract pre
    Requires( wToken != nullptr );
    Requires( wToken.is_ptr_valid() );

    // 1# If token is not valid yet, remove it from the 'to write' bucket
    if (!wToken->valid()) {
        owner<VertexBufferToken> oToken = extract_owner(_tokens, wToken);
        oToken.destroy();

        _writeBucket.erase(wToken);
        return;
    }

    // 2# Create RemoveOp for token
    _removeBucket.push_back( wToken );
}

template<class T>
inline void VertexBuffer<T>::clear()
{
    for ( auto& token : _tokens ) {
        remove_vertices( token.get_non_owner() );
    }
    commit_remove();
    _writeBucket.clear();

    Ensures( num_vertices() == 0 );
}

template<class T>
void VertexBuffer<T>::commit_write() {
    // 0# Contract pre
    Guard( _writeBucket.size() > 0 ) return;

    // 1# Do WriteOps
    for (auto it = _writeBucket.begin(); it != _writeBucket.end(); it++) {
        auto token = it->first;
        auto vertices = it->second;

        commit_write( std::move(vertices) , token);
        _numVertices += token->object_range().length();
    }

    _writeBucket.clear();

    // X# Contract Post
    Ensures( _writeBucket.size() == 0 );
}

template<class T>
void VertexBuffer<T>::commit_remove() {
    // 1# Search for unnused tokens and remove them
    for (auto it = _tokens.begin(); it != _tokens.end();) {
        if (it->ref_count() == 1) {
            it->destroy();
            _tokens.erase( it );
        }
        else {
            it++;
        }
    }

    // 2# Do RemoveOps
    for (auto removeToken : _removeBucket) {
        commit_remove( removeToken );
        _numVertices -= removeToken->object_range().length();

        owner<VertexBufferToken> oToken = extract_owner( _tokens, removeToken );
        oToken.destroy();
    }
    _removeBucket.clear();

    // X# Contract Post
    Ensures( _removeBucket.size() == 0 );
}

template<class T>
uint32 VertexBuffer<T>::num_vertices() const 
{
    return _numVertices;
}

template<class T>
bool VertexBuffer<T>::contains(weak<VertexBufferToken> token) const
{
    return contains_owner( _tokens, token );
}

template<class T>
uint32 VertexBuffer<T>::object_size() const
{
    return _layout.bytesize();
}

template<class T>
uint32 VertexBuffer<T>::object_capacity() const
{
    return _atomCapacity / _layout.bytesize();
}

template<class T>
uint32 VertexBuffer<T>::atom_capacity() const
{
    return _atomCapacity;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                       Protected                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
void VertexBuffer<T>::native_write_at(uint32 index, std::vector<float> data) {
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferSubData(GL_ARRAY_BUFFER, index, data.size() * FLOAT_BYTES, data.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<class T>
void VertexBuffer<T>::native_remove_at(uint32 index, uint32 length) {
    // Save the remove operations and just ignore the data
}

template<class T>
void VertexBuffer<T>::native_resize(uint32 oldCapacity, uint32 newCapacity)
{
    // 1# Create temporary copy of VBO
    GLuint tempVboId = createVBO(oldCapacity);

    // 2# Copy content into temporary VBO
    glBindBuffer(GL_COPY_READ_BUFFER, _vboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, tempVboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);

    // 3# Resize VBO
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, newCapacity, NULL, GL_STATIC_DRAW);

    // 4# Copy content back into original VBO
    glBindBuffer(GL_COPY_READ_BUFFER, tempVboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, _vboId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);

    // 5# Cleanup
    glDeleteBuffers(1, &tempVboId);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

template<class T>
void VertexBuffer<T>::commit_write( std::vector<T> vertices, weak<VertexBufferToken> token)
{
    // 0# Contract Pre
    Guard(vertices.size() > 0) return;

    Requires( token != nullptr );
    Requires( token.is_ptr_valid() );

    // 1# Get free range
    uint32_t size = (uint32_t)vertices.size() * object_size();

    uint32 freeRangeId = get_free_range(size);
    Range freeRange = _freeRanges[freeRangeId];

    _freeRanges.erase(freeRangeId);
    _usedRanges[freeRangeId] = freeRange;

    // 2# Bring data into native format
    std::vector<float> data;
    for (T vertex : vertices) {
        data.insert(data.end(), vertex.data.begin(), vertex.data.end());

        std::ostringstream debugMsg;
        debugMsg << "WRITE VERTEX ["; for (float flt : vertex.data ) { debugMsg << flt << " "; } debugMsg << "]";
        LOGGER.log(Level::DEBUG) << debugMsg.str() << "\n";
    }

    // 3# Write
    LOGGER.log(Level::DEBUG) << "WRITE " << vertices.size() << " AT [" << freeRange.index() << ", " << freeRange.last_index() << "]\n";
    native_write_at(freeRange.index(), std::move( data ));

    // 4# Update and validate the token
    token->set_range_id(freeRangeId);
    token->set_atom_range(freeRange);
    token->set_object_size(object_size());
    token->validate();

    // 4# Contract Post
    Ensures(token->valid());
}

template<class T>
void VertexBuffer<T>::commit_remove(weak<VertexBufferToken> token)
{
    // 0# Contract Pre
    Requires( token.is_ptr_valid() );
    Requires( token != nullptr );

    // 1# Get used range
    uint32 rangeId = token->range_id();

    if (_usedRanges.count( rangeId ) == 0) {
        LOGGER.log(Level::WARN) << "Attempting to remove unkown range with id: " << rangeId << "\n";
        return;
    }

    Range range = _usedRanges[rangeId];

    // 2# Remove range
    native_remove_at(range.index(), range.length());

    _usedRanges.erase(rangeId);
    _freeRanges[rangeId] = range;

    // 3# Invalidate token
    token->invalidate();

    // 4# Contract Post
    Ensures(!token->valid());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


template<class T>
void VertexBuffer<T>::optimize_free_ranges() {
    bool hasChanged = false;

    do {
        hasChanged = _optimize_free_ranges();
    } while (hasChanged);
}

template<class T>
bool VertexBuffer<T>::_optimize_free_ranges() {

    for (auto it0 = _freeRanges.begin(); it0 != _freeRanges.end(); ++it0) {
        for (auto it1 = _freeRanges.begin(); it1 != _freeRanges.end(); ++it1) {

            auto range1Id = it0->first;
            auto range1 = it0->second;

            auto range2Id = it1->first;
            auto range2 = it1->second;

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
void VertexBuffer<T>::merge_free_ranges(uint32 range1Id, uint32 range2Id) {
    // 0# Guards
    Guard( _freeRanges.count(range1Id) > 0 ) return;
    Guard( _freeRanges.count(range2Id) > 0 ) return;

    // 1# Get ranges to merge
    Range range1 = _freeRanges[range1Id];
    Range range2 = _freeRanges[range2Id];

    if (range1.index() + range1.length() != range2.index()) {
        LOGGER.log(Level::WARN) << "Attempting to merge non-adjacent ranges with id: " << range1Id << ", " << range2Id << "\n";
        return;
    }

    // 2# Create new range
    uint32 mergedRangeId = _rangeIDGen.new_id();
    auto mergedRange = Range( range1.index(), range1.length() + range2.length() );

    // 3# Swap out ranges
    _freeRanges.erase(range1Id);
    _freeRanges.erase(range2Id);
    _freeRanges[ mergedRangeId ] = mergedRange;
}

template<class T>
uint32 VertexBuffer<T>::get_free_range(uint32 length) {
    // 1# Find a range with range.length >= length
    optional<uint32> optionalRangeId;

    for (auto it = _freeRanges.begin(); it != _freeRanges.end(); ++it) {
        if (it->second.length() >= length) {
            optionalRangeId = it->first;
            break;
        }
    }

    // 2.1# If no range found: resize, search again
    if ( !optionalRangeId.has_value() ) {
        resize(atom_capacity(), atom_capacity() + length);

        for (auto it = _freeRanges.begin(); it != _freeRanges.end(); ++it) {
            if (it->second.length() >= length) {
                optionalRangeId = it->first;
                break;
            }
        }

        if (!optionalRangeId.has_value()) {
            throw std::logic_error("No free range found after resizing! Make sure resizing is implemented properly!");
        }
    }

    Range range = _freeRanges[optionalRangeId.value()];

    // 2.2# If range is larger than needed, split
    if (range.length() > length) {
        uint32 newRange1Id = _rangeIDGen.new_id();
        auto newRange1 = Range(range.index(), length);

        uint32 newRange2Index = newRange1.index() + newRange1.length();
        uint32 newRange2Length = range.length() - length;
        auto newRange2 = Range(newRange2Index, newRange2Length);

        _freeRanges.erase(optionalRangeId.value());
        _freeRanges[ newRange1Id ] = newRange1;
        _freeRanges[_rangeIDGen.new_id() ] = newRange2;

        return newRange1Id;
    }
    // 2.3# else return found range id
    else {
        return optionalRangeId.value();
    }
}

template<class T>
void VertexBuffer<T>::resize(uint32 oldAtomCapacity, uint32 newAtomCapacity) {
    native_resize(oldAtomCapacity, newAtomCapacity);

    _atomCapacity = newAtomCapacity;

    auto additionalFreeRange = Range(oldAtomCapacity, newAtomCapacity - oldAtomCapacity);
    _freeRanges[ _rangeIDGen.new_id() ] = additionalFreeRange;

    optimize_free_ranges();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
GLuint VertexBuffer<T>::createVBO(uint32 capacityBytes) {
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, capacityBytes, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}

template<class T>
Logger VertexBuffer<T>::LOGGER = Logger("VertexBuffer<>", Level::WARN);

ENGINE_NAMESPACE_END