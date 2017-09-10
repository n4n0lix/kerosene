#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <functional>
#include <algorithm>

// Other Includes
#include "list.h"

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class K, class V>
class Map
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                    put(K key, V value);

    size_t                  size();
    bool                    contains(K key) const;
    bool                    empty();
    V                       get(K key);
    list<V>                 values();
    list<K>                 keys() const;
    list<pair<K, V>>        as_vector();
	void					clear();

    bool                    remove(K key);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    map<K, V> _map;
};

template<class K, class V>
void Map<K, V>::put(K key, V value)
{
    _map[key] = value;
}

template<class K, class V>
size_t Map<K, V>::size()
{
    return _map.size();
}

template<class K, class V>
bool Map<K, V>::contains(K key) const
{
    return _map.find(key) != _map.end();
}

template<class K, class V>
bool Map<K, V>::empty()
{
    return _map.empty();
}

template<class K, class V>
V Map<K, V>::get(K key)
{
    return _map[key];
}

template<class K, class V>
list<V> Map<K, V>::values()
{
    list<V> values = list<V>();

    for (pair<K,V> entry: _map) {
        if (!values.contains(entry.second)) {
            values.add(entry.second);
        }
    }

    return std::move( values );
}

template<class K, class V>
list<K> Map<K, V>::keys() const
{
    list<V> keys = list<V>();

    for (pair<K, V> entry : _map) {
        keys.add(entry.first);
    }

    return std::move( keys );
}

template<class K, class V>
list<pair<K, V>> Map<K, V>::as_vector()
{
    list<pair<K, V>> result;
    for (auto pair : _map) {
        result.add(std::pair<K,V>(pair));
    }
    return result;
}

template<class K, class V>
inline void Map<K, V>::clear()
{
	_map.clear();
}

template<class K, class V>
bool Map<K, V>::remove(K key)
{
    return _map.erase(key) != 0;
}

ENGINE_NAMESPACE_END

