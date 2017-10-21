#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

ENGINE_NAMESPACE_BEGIN

// Extend if the class is NOT meant to manage ownership and 
// only hold a value, and therefore is trivially copyable.
struct Value {
    Value()                           = default;  // Constructor
    Value( Value&& )                  = default;  // Move-Constructor
    Value& operator=( Value&& )       = default;  // Move-Operator
    ~Value()                          = default;  // Destructor
    Value( const Value& )             = default;  // Copy-Constructor
    Value& operator=( const Value& )  = default;  // Copy-Operator
};

ENGINE_NAMESPACE_END