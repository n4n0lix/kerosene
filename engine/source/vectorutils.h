#pragma once

// Std-Includes
#include <algorithm>
        using std::max;

#include <vector>
        using std::vector;
        using std::find;
        using std::swap;
        using std::remove;

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Enum                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
class DLL_PUBLIC VectorUtils {

public:
    INLINE static bool contains(vector<T> vector, T object);

    INLINE static bool remove(vector<T> vector, T object);

    INLINE static void add(vector<T> vector, T object);
};

template<class T>
bool VectorUtils<T>::contains(vector<T> vector, T object) {
    return std::find(vector.begin(), vector.end(), object) != vector.end();
}

template<class T>
bool VectorUtils<T>::remove(vector<T> vector, T object) {
    size_t oldSize = vector.size();
    vector.erase(std::remove(vector.begin(), vector.end(), object), vector.end());
    return oldSize != vector.size();
}

template<class T>
void VectorUtils<T>::add(vector<T> vector, T object) {
    vector.push_back(object);
}

ENGINE_NAMESPACE_END


