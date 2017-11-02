#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include "noncopyable.h"
#include "owner.h"



// Focus on:
//  - fast accessing
//      - fast iterating over all elements (cache-friendly)
//      - fast random access
//
// Tradeoffs:
//  - increased memory space usage
//  - slower inserts & removes
//
// Assumptions:
//  - Stored data will be significantly larger than the keys, 
//    therefore value capacity is flexible and dynamically grows

struct compact_map_t {
    virtual ~compact_map_t() = default;
};

template<typename K, typename V>
class compact_map : public compact_map_t
{
public:
    // Enabled:
    compact_map();
    compact_map( compact_map<K, V>&& );
    compact_map& operator=( compact_map<K,V>&& );
    ~compact_map() {
        delete _values;
        delete _keys;
    };

    // Disabled:
    compact_map( const compact_map& ) = delete;               // Copy-Constructor
    compact_map& operator=( const compact_map& ) = delete;    // Copy-Operator

    void    put( K key, V value );
    V&      access( K key );
    void    remove( K key );
    bool    contains( K key );

    std::vector<V>& values();

private:
    // Values
    std::vector<V>*      _values;
    std::map<K, size_t>* _keys;

    static void         __move_state( compact_map<K,V>& dest, compact_map<K, V>& src );
};

template<typename K, typename V>
compact_map<K,V>::compact_map() {
    _values = new std::vector<V>();
    _keys = new std::map<K, size_t>();
}

template<typename K, typename V>
void compact_map<K, V>::put( K key, V value )
{
    _values->push_back( value );
    _keys->insert( std::pair<K, size_t>( key, _values->size()-1 ) );
}

template<typename K, typename V>
V& compact_map<K, V>::access( K key )
{
    auto& index = (*_keys)[key];
    auto& value = (*_values)[index];

    return value;
}

template<typename K, typename V>
void compact_map<K, V>::remove( K key )
{
    if ( _keys->erase( key ) == 0 )
        return;

    size_t index = _keys->find( key );
    _values->erase( _values.begin() + index );

    for ( auto& pair : *_keys ) {
        if ( pair.second > index )
            pair.second--;
    }
}

template<typename K, typename V>
bool compact_map<K, V>::contains( K key )
{
    return _keys->count(key) > 0;
}

template<typename K, typename V>
std::vector<V>& compact_map<K, V>::values()
{
    return *_values;
}

#pragma region Move Semantics
template<typename K, typename V>
compact_map<K, V>::compact_map( compact_map<K,V>&& o )
{
    __move_state( this, o );
}

template<typename K, typename V>
compact_map<K, V>& compact_map<K, V>::operator=( compact_map<K,V>&& o )
{
    __move_state( this, o );
    return this;
}

template<typename K, typename V>
void compact_map<K, V>::__move_state( compact_map<K, V>& dest, compact_map<K, V>& src ) {
    dest._values = src._values;
    src._values = nullptr;

    dest._keys = src._keys;
    dest._keys = nullptr;
}
#pragma endregion