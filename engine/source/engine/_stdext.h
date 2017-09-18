#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <vector>
#include <algorithm>

// Other Includes

// Internal Includes

namespace ext {

    template<class T>
    bool contains( vector<T>& vector, const T& val ) {
        return std::find( vector.begin(), vector.end(), val ) != vector.end();
    }

    template<class T>
    int32_t index_of( vector<T>& vector, const T& val ) {
        auto iter = std::find( vector.begin(), vector.end(), val );

        if ( iter != vector.end() ) {
            return std::distance( iter, vector.end() );
        }
        else {
            return -1;
        }
    }

}
