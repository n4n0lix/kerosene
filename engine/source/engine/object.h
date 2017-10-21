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
struct Object {
    // Enabled:
    Object()                        = default;  // Constructor
    Object( Object&& )              = default;  // Move-Constructor
    Object& operator=( Object&& )   = default;  // Move-Operator
    virtual ~Object()               = default;  // Destructor

    // Disabled:
    Object( const Object& )             = delete;    // Copy-Constructor
    Object& operator=( const Object& )  = delete;    // Copy-Operator
};

ENGINE_NAMESPACE_END