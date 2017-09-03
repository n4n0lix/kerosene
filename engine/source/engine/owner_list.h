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
#include "nullable.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
class owner_list : public vector<owner<T>>
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                    add(owner<T> object);

    size_t                  remove(size_t index);
    size_t                  remove(T* object);
    size_t                  remove(std::function<bool(owner<T>&)> func);

    owner<T>                extract(size_t index);
    owner<T>                extract(T* object);

    size_t                  index_of(T* object);

    bool                    contains(T* object);

    void                    for_all(std::function<void(owner<T>&)> func);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    list<T> _nonOwnerList;
};

template<class T>
void owner_list<T>::add(owner<T> object)
{
    this->push_back( move(object) );
}

template<class T>
size_t owner_list<T>::remove(size_t index)
{
    if (!(index >= 0 && index < size())) { return 0; }

    size_t oldSize = size();
    erase(begin() + index);
    return oldSize - size();
}

template<class T>
size_t owner_list<T>::remove(T* object)
{
    if (object == nullptr) { return 0; }
	return remove( index_of(object) );
}

template<class T>
size_t owner_list<T>::remove(std::function<bool(owner<T>&)> func)
{
    size_t oldSize = size();
    erase(std::remove_if(begin(), end(), func), end());
    return oldSize - size();
}

template<class T>
owner<T> owner_list<T>::extract(size_t index)
{
    if (!(index >= 0 && index < size())) { return nullptr; }

    owner<T> result = move( at(index) );
    remove(index);
    return move(result);
}

template<class T>
owner<T> owner_list<T>::extract(T* object)
{
    return move( extract( index_of(object) ) );
}

template<class T>
inline size_t owner_list<T>::index_of(T* object)
{
    for (size_t i = 0; i < size(); i++) {
        owner<T>& p = at(i);

        if (p.get() == object) {
            return i;
        }
    }

    return -1;
}

template<class T>
bool owner_list<T>::contains(T* object)
{
    for (size_t i = 0; i < size(); i++) {
        owner<T>& p = at(i);

        if (p.get() == object) {
            return true;
        }
    }

    return false;
}

template<class T>
void owner_list<T>::for_all(std::function<void(owner<T>&)> func)
{
    std::for_each(begin(), end(), func);
}

ENGINE_NAMESPACE_END

