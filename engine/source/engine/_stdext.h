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
    inline bool contains( std::vector<T>& pVector, const T& val ) {
        return std::find( pVector.begin(), pVector.end(), val ) != pVector.end();
    }

    template<class T>
    inline int32_t index_of( std::vector<T>& pVector, const T& val ) {
        auto iter = std::find( pVector.begin(), pVector.end(), val );

        if ( iter != pVector.end() ) {
            return std::distance( iter, pVector.end() );
        }
        else {
            return -1;
        }
    }

}
