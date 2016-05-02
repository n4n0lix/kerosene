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

    void    add(T& object);

    size_t  remove(T& object);
    size_t  remove(std::function<bool(T&)> func);

    bool    contains(T& object);

    void    forAll(std::function<void(T&)> func);

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


ENGINE_NAMESPACE_END

