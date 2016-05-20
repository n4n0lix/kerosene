#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <functional>
#include <algorithm>

// Other Includes

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

    bool                    contains(K key);
    V                       get(K key);
    shared_ptr<Vector<V>>   values();
    shared_ptr<Vector<K>>   keys();
    Vector<pair<K, V>>      as_vector();

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
bool Map<K, V>::contains(K key)
{
    return _map.find(key) != _map.end();
}

template<class K, class V>
V Map<K, V>::get(K key)
{
    return _map[key];
}

template<class K, class V>
shared_ptr<Vector<V>> Map<K, V>::values()
{
    shared_ptr<Vector<V>> values = make_shared<Vector<V>>();

    for (pair<K,V> entry: _map) {
        if (!values->contains(entry.second)) {
            values->add(entry.second);
        }
    }

    return values;
}

template<class K, class V>
shared_ptr<Vector<K>> Map<K, V>::keys()
{
    shared_ptr<Vector<V>> keys = make_shared<Vector<V>>();

    for (pair<K, V> entry : _map) {
        keys->add(entry.first);
    }

    return keys;
}

template<class K, class V>
Vector<pair<K, V>> Map<K, V>::as_vector()
{
    Vector<pair<K, V>> result;
    for (auto pair : _map) {
        result.push_back(std::pair<K,V>(pair));
    }
    return result;
}

template<class K, class V>
bool Map<K, V>::remove(K key)
{
    return _map.erase(key) != 0;
}

ENGINE_NAMESPACE_END

