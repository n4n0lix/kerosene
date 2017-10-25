#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

ENGINE_NAMESPACE_BEGIN

// Extend if the class is meant to manage ownership and 
// therefore trivial copying is not intended.
struct noncopyable {
    // Enabled:
    noncopyable()                        = default;  // Constructor
    noncopyable( noncopyable&& )              = default;  // Move-Constructor
    noncopyable& operator=( noncopyable&& )   = default;  // Move-Operator
    virtual ~noncopyable()               = default;  // Destructor

    // Disabled:
    noncopyable( const noncopyable& )             = delete;    // Copy-Constructor
    noncopyable& operator=( const noncopyable& )  = delete;    // Copy-Operator
};

ENGINE_NAMESPACE_END