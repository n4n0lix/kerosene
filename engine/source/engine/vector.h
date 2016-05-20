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
class Vector : public vector<T>
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                    add(T& object);

    size_t                  remove(T& object);
    size_t                  remove(std::function<bool(T&)> func);

    bool                    contains(T& object);

    void                    forAll(std::function<void(T&)> func);

    void                    collect(Vector<T>& dest, std::function<bool(T&)> func);
    shared_ptr<Vector<T>>   collect(std::function<bool(T&)> func);

    Nullable<T>             first(std::function<bool(T&)> func);
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

template<class T>
void Vector<T>::add(T& object)
{
    this->push_back(object);
}

template<class T>
size_t Vector<T>::remove(T & object)
{
    size_t oldSize = size();
    erase(std::remove(begin(), end(), object), end());
    return oldSize - size();
}

template<class T>
size_t Vector<T>::remove(std::function<bool(T&)> func)
{
    size_t oldSize = size();
    erase(std::remove_if(begin(), end(), func), end());
    return oldSize - size();
}

template<class T>
bool Vector<T>::contains(T & object)
{
    return std::find(begin(), end(), object) != end();
}

template<class T>
void Vector<T>::forAll(std::function<void(T&)> func)
{
    std::for_each(begin(), end(), func);
}

template<class T>
void Vector<T>::collect(Vector<T>& dest, std::function<bool(T&)> func)
{
    std::for_each(begin(), end(), [&](T& obj) -> void {
        if (func(obj)) {
            dest.add(obj);
        }
    });
}

template<class T>
shared_ptr<Vector<T>> Vector<T>::collect(std::function<bool(T&)> func)
{
    shared_ptr<Vector<T>> objects = make_shared<Vector<T>>();
    collect(*(objects->get()), func);
    return objects;
}

template<class T>
Nullable<T> Vector<T>::first(std::function<bool(T&)> func)
{
    for (T t : *this) {
        if (func(t)) {
            return Nullable<T>(t);
        }
    }

    return Nullable<T>();
}


ENGINE_NAMESPACE_END

