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
class UniquePtrVector : public vector<u_ptr<T>>
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                    add(u_ptr<T> object);

    size_t                  remove(size_t index);
    size_t                  remove(T* object);
    size_t                  remove(std::function<bool(u_ptr<T>&)> func);

    u_ptr<T>                extract(size_t index);
    u_ptr<T>                extract(T* object);

    size_t                  index_of(T* object);

    bool                    contains(T* object);

    void                    forAll(std::function<void(u_ptr<T>&)> func);
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

template<class T>
void UniquePtrVector<T>::add(u_ptr<T> object)
{
    this->push_back( move(object) );
}

template<class T>
size_t UniquePtrVector<T>::remove(size_t index)
{
    if (!(index >= 0 && index < size())) { return 0; }

    size_t oldSize = size();
    erase(begin() + index);
    return oldSize - size();
}

template<class T>
size_t UniquePtrVector<T>::remove(T* object)
{
    if (object == nullptr) { return 0; }
	return remove( index_of(object) );
}

template<class T>
size_t UniquePtrVector<T>::remove(std::function<bool(u_ptr<T>&)> func)
{
    size_t oldSize = size();
    erase(std::remove_if(begin(), end(), func), end());
    return oldSize - size();
}

template<class T>
u_ptr<T> UniquePtrVector<T>::extract(size_t index)
{
    if (!(index >= 0 && index < size())) { return nullptr; }

    u_ptr<T> result = move( at(index) );
    remove(index);
    return move(result);
}

template<class T>
u_ptr<T> UniquePtrVector<T>::extract(T* object)
{
    return move( extract( index_of(object) ) );
}

template<class T>
inline size_t UniquePtrVector<T>::index_of(T* object)
{
    for (size_t i = 0; i < size(); i++) {
        u_ptr<T>& p = at(i);

        if (p.get() == object) {
            return i;
        }
    }

    return -1;
}

template<class T>
bool UniquePtrVector<T>::contains(T* object)
{
    for (size_t i = 0; i < size(); i++) {
        u_ptr<T>& p = at(i);

        if (p.get() == object) {
            return true;
        }
    }

    return false;
}

template<class T>
void UniquePtrVector<T>::forAll(std::function<void(u_ptr<T>&)> func)
{
    std::for_each(begin(), end(), func);
}

ENGINE_NAMESPACE_END

