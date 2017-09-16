#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "matrix4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class Uniform {
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    Uniform()                                               : type(""), name(""), location(-1) { }
    Uniform(string type, string name , int32 location = -1) : type(type), name(name), location(location) { }
    ~Uniform() = default;

    string  type;
    string  name;
    int32   location;

    bool operator<(const Uniform& o1) const { return name == o1.name ? type < o1.type : name < o1.name; }
    bool operator==(const Uniform& o) const { return type == o.type && name == o.name; }
    bool operator!=(const Uniform& o) const { return !(*this == o); }
};

ENGINE_NAMESPACE_END
