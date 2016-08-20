#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

struct Uniform {
    string  type;
    string  name;
    GLint   location;

    bool operator<(const Uniform& o1) const { return name == o1.name ? type < o1.type : name < o1.name; }
    bool operator==(const Uniform& o) const { return type == o.type && name == o.name; }
    bool operator!=(const Uniform& o) const { return !(*this == o); }
};

ENGINE_NAMESPACE_END
