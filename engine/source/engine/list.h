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
class list : public vector<T>
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                    add(const T& object);

    size_t                  remove_at(size_t index);
	size_t                  remove_by_predicate(std::function<bool(T&)> func);

    size_t                  remove(T& object);

    bool                    contains(T& object);
	bool					contains_r(T& object);

    void                    forAll(std::function<void(T&)> func);

    void                    collect(list<T>& dest, std::function<bool(T&)> func);
    shared_ptr<list<T>>     collect(std::function<bool(T&)> func);

    Nullable<T>             first(std::function<bool(T&)> func);
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

template<class T>
void list<T>::add(const T& object)
{
    this->push_back( object );
}

template<class T>
size_t list<T>::remove_at(size_t index)
{
    if (!(index >= 0 && index < size())) { return 0; }

    size_t oldSize = size();
    erase(begin() + index);
    return oldSize - size();
}

template<class T>
size_t list<T>::remove_by_predicate(std::function<bool(T&)> func)
{
	size_t oldSize = size();
	erase(std::remove_if(begin(), end(), func), end());
	return oldSize - size();
}

template<class T>
size_t list<T>::remove(T& object)
{
    size_t oldSize = size();
    erase(std::remove(begin(), end(), object), end());
    return oldSize - size();
}

//template<class T>
//size_t list<T>::remove(T* object)
//{
//	size_t oldSize = size();
//	erase(std::remove(begin(), end(), object), end());
//	return oldSize - size();
//}

template<class T>
bool list<T>::contains(T& object)
{
    return std::find(begin(), end(), object) != end();
}

template<class T>
bool list<T>::contains_r(T& object)
{
	return std::find(rbegin(), rend(), object) != rend();
}

template<class T>
void list<T>::forAll(std::function<void(T&)> func)
{
    std::for_each(begin(), end(), func);
}

template<class T>
void list<T>::collect(list<T>& dest, std::function<bool(T&)> func)
{
    std::for_each(begin(), end(), [&](T& obj) -> void {
        if (func(obj)) {
            dest.add(obj);
        }
    });
}

template<class T>
shared_ptr<list<T>> list<T>::collect(std::function<bool(T&)> func)
{
    shared_ptr<list<T>> objects = make_shared<list<T>>();
    collect(*(objects->get()), func);
    return objects;
}

template<class T>
Nullable<T> list<T>::first(std::function<bool(T&)> func)
{
    for (T t : *this) {
        if (func(t)) {
            return Nullable<T>(t);
        }
    }

    return Nullable<T>();
}


ENGINE_NAMESPACE_END

