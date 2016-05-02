#pragma once

// Std-Includes
#include <algorithm>

#include <vector>
        using std::vector;
        using std::find;
        using std::remove;

// Other Includes

// Internal Includes

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Enum                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
class VectorUtils {

public:
    static bool contains(const vector<T>& vector, T object);

    static bool remove(vector<T>& vector, T object);

    static void add(vector<T>& vector, T object);
};

template<typename T>
bool VectorUtils<T>::contains(const vector<T>& vector, T object) {
    return std::find(vector.cbegin(), vector.cend(), object) != vector.cend();
}

template<typename T>
bool VectorUtils<T>::remove(vector<T>& vector, T object) {
    size_t oldSize = vector.size();
    vector.erase(std::remove(vector.begin(), vector.end(), object), vector.end());
    return oldSize != vector.size();
}

template<typename T>
void VectorUtils<T>::add(vector<T>& vector, T object) {
    vector.push_back(object);
}


