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
#include "list.h"
#include "map.h"

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "_renderdefs.h"

#include "idgenerator.h"
#include "logger.h"

#include "range.h"

#include "buffer.h"
#include "vertexbuffertoken.h"

#include "vertexlayout.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
struct WriteOp {
    shared<VertexBufferToken>    token;
    list<T>                     vertices;
};

template<class T>
class VertexBuffer
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                    VertexBuffer(VertexLayout layout, uint32 initCapacity);
                                    ~VertexBuffer();

            GLuint                          get_id()            const;
            uint32                          object_size()       const;
            uint32                          object_capacity()   const;
            uint32                          atom_capacity()     const;

            shared_ptr<VertexBufferToken>   add_vertices(list<T> vertices);
            void                            remove_vertices(shared_ptr<VertexBufferToken> token);

            void                            commit_write();
            void                            commit_remove();

            virtual uint32                  num_vertices()      const;
            bool                            contains(shared_ptr<VertexBufferToken> token) const;

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    const   list<shared_ptr<VertexBufferToken>>&    get_tokens();

            void                                    native_remove_at(uint32 index, uint32 length);
            void                                    native_resize(uint32 oldCapacity, uint32 newCapacity);
            
            void                                    commit_write(list<T> objects, shared_ptr<VertexBufferToken> token);
            void                                    commit_remove(shared_ptr<VertexBufferToken> token);

            void                                    native_write_at(uint32 index, vector<float> data);

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
    uint32                _capacity;
    uint32                _atomCapacity;

    VertexLayout          _layout;

    Map<uint32, Range>    _freeRanges;
    Map<uint32, Range>    _usedRanges;
    Map<shared<VertexBufferToken>, list<T>> _writeBucket;

    list<shared<VertexBufferToken>>      _removeBucket;
    list<shared<VertexBufferToken>>      _tokens;

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
VertexBuffer<T>::VertexBuffer(VertexLayout layout, uint32 initCapacity) {
    // 1# Set members
    _layout = layout;
    _numVertices = 0;
    _atomCapacity = layout.bytesize() * initCapacity;

    // 2# Buffer Mgmt
    auto initialRange = Range(0, _atomCapacity);
    _freeRanges.put(_rangeIDGen.new_id(), initialRange); 
    LOGGER.log(Level::DEBUG) << "CREATE [" << initialRange.index() << "," << initialRange.last_index() << "], OBJ SIZE: " << object_size() << "\n";

    // 3# OpenGL
    _vboId = createVBO(_atomCapacity);
    LOGGER.log(Level::DEBUG, _vboId) << "CREATE" << endl;

    // X# Contract Post
    Ensures(!_freeRanges.empty());
}

template<class T>
VertexBuffer<T>::~VertexBuffer()
{
    LOGGER.log(Level::DEBUG, _vboId) << "DELETE" << endl;
    glDeleteBuffers( 1, &_vboId );
}

template<class T>
GLuint VertexBuffer<T>::get_id() const 
{
    return _vboId;
}

template<class T>
shared_ptr<VertexBufferToken> VertexBuffer<T>::add_vertices(list<T> vertices)
{
    LOGGER.log(Level::DEBUG, _vboId) << "ADD " << vertices.size() << " vertices" << endl;

    // 1# Guards
    Requires(!vertices.empty());

    // 2# Create token
    shared<VertexBufferToken> token = make_shared<VertexBufferToken>( _tokenIDGen.new_id(), this);

    // 3# Store in write bucket
    _writeBucket.put(token, std::move(vertices));
    //_writeBucket2.insert( make_pair<s_ptr<VertexBufferToken>, list<T>>( std::move(token), std::move(vertices) );

    // 4# Return token
    return token;
}

template<class T>
void VertexBuffer<T>::remove_vertices(shared<VertexBufferToken> token)
{
    // 0# Contract pre
    Requires(token != nullptr);

    // 1# If token is not valid yet, remove it from the 'to write' bucket
    if (!token->valid()) {
        _writeBucket.remove( token );
        return;
    }

    // 2# Create RemoveOp for token
    _removeBucket.add( token );
}

template<class T>
const list<shared<VertexBufferToken>>& VertexBuffer<T>::get_tokens()
{
    return _tokens;
}

template<class T>
void VertexBuffer<T>::commit_write() {
    // 0# Contract pre
    Guard( !_writeBucket.empty() ) return;

    // 1# Do WriteOps
    for (auto writeOp : _writeBucket.as_vector()) {
        auto token = writeOp.first;
        auto vertices = writeOp.second;

        commit_write( std::move(vertices), token );
        _numVertices += token->object_range().length();

        _tokens.add( token );
    }
    _writeBucket.clear();

    // X# Contract Post
    Ensures( _writeBucket.empty() );
}

template<class T>
void VertexBuffer<T>::commit_remove() {
    // 1# Search for unnused tokens and remove them
    for (auto token : _tokens) {
        if (token.use_count() == 1) {
            _removeBucket.add(token);
        }
    }

    // 2# Do RemoveOps
    for (auto removeToken : _removeBucket) {
        commit_remove(removeToken);
        _numVertices -= removeToken->object_range().length();
        _tokens.remove(removeToken);
    }
    _removeBucket.clear();

    // X# Contract Post
    Ensures(_removeBucket.empty());
}

template<class T>
uint32 VertexBuffer<T>::num_vertices() const 
{
    return _numVertices;
}

template<class T>
bool VertexBuffer<T>::contains(shared_ptr<VertexBufferToken> token) const
{
    return _tokens.contains(token) || _writeBucket.contains(token);
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
void VertexBuffer<T>::native_write_at(uint32 index, vector<float> data) {
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
void VertexBuffer<T>::commit_write(list<T> vertices, shared_ptr<VertexBufferToken> token)
{
    // 0# Contract Pre
    Guard(vertices.size() > 0) return;

    Requires(token != nullptr);

    // 1# Get free range
    uint32_t size = (uint32_t)vertices.size() * object_size();

    uint32 freeRangeId = get_free_range(size);
    Range freeRange = _freeRanges.get(freeRangeId);

    _freeRanges.remove(freeRangeId);
    _usedRanges.put(freeRangeId, freeRange);

    // 2# Bring data into native format
    vector<float> data;
    for (T vertex : vertices) {
        vector<float> vertexData = vertex.data();
        data.insert(data.end(), vertexData.begin(), vertexData.end());

        std::ostringstream debugMsg;
        debugMsg << "WRITE VERTEX ["; for (float flt : vertexData) { debugMsg << flt << " "; } debugMsg << "]";
        LOGGER.log(Level::DEBUG) << debugMsg.str() << endl;
    }

    // 3# Write
    LOGGER.log(Level::DEBUG) << "WRITE " << vertices.size() << " AT [" << freeRange.index() << ", " << freeRange.last_index() << "]" << endl;
    native_write_at(freeRange.index(), move( data ));

    // 4# Update and validate the token
    token->set_range_id(freeRangeId);
    token->set_atom_range(freeRange);
    token->set_object_size(object_size());
    token->validate();

    // 4# Contract Post
    Ensures(token->valid());
}

template<class T>
void VertexBuffer<T>::commit_remove(shared_ptr<VertexBufferToken> token)
{
    // 0# Contract Pre

    // 1# Get used range
    uint32 rangeId = token->range_id();

    if (!_usedRanges.contains(rangeId)) {
        LOGGER.log(Level::WARN) << "Attempting to remove unkown range with id: " << rangeId << endl;
        return;
    }

    Range range = _usedRanges.get(rangeId);

    // 2# Remove range
    native_remove_at(range.index(), range.length());

    _usedRanges.remove(rangeId);
    _freeRanges.put(rangeId, range);

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
void VertexBuffer<T>::merge_free_ranges(uint32 range1Id, uint32 range2Id) {
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
    uint32 mergedRangeId = _rangeIDGen.new_id();
    auto mergedRange = Range(range1.index(), range1.length() + range2.length());

    // 3# Swap out ranges
    _freeRanges.remove(range1Id);
    _freeRanges.remove(range2Id);
    _freeRanges.put(mergedRangeId, mergedRange);
}

template<class T>
uint32 VertexBuffer<T>::get_free_range(uint32 length) {
    // 1# Find a range with range.length >= length
    Nullable<uint32> optionalRangeId;

    for (auto pair : _freeRanges.as_vector()) {
        if (pair.second.length() >= length) {
            optionalRangeId = pair.first;
        }
    }

    // 2.1# If no range found: resize, search again
    if (optionalRangeId.is_null()) {
        resize(atom_capacity(), atom_capacity() + length);

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
        uint32 newRange1Id = _rangeIDGen.new_id();
        auto newRange1 = Range(range.index(), length);

        uint32 newRange2Index = newRange1.index() + newRange1.length();
        uint32 newRange2Length = range.length() - length;
        auto newRange2 = Range(newRange2Index, newRange2Length);

        _freeRanges.remove(optionalRangeId.get());
        _freeRanges.put( newRange1Id, newRange1 );
        _freeRanges.put( _rangeIDGen.new_id() , newRange2);

        return newRange1Id;
    }
    // 2.3# else return found range id
    else {
        return optionalRangeId.get();
    }
}

template<class T>
void VertexBuffer<T>::resize(uint32 oldAtomCapacity, uint32 newAtomCapacity) {
    native_resize(oldAtomCapacity, newAtomCapacity);

    _atomCapacity = newAtomCapacity;

    auto additionalFreeRange = Range(oldAtomCapacity, newAtomCapacity - oldAtomCapacity);
    _freeRanges.put( _rangeIDGen.new_id(), additionalFreeRange );

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