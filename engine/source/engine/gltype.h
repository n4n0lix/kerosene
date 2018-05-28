#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "_gl.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class GLType {
public:
    static GLType FLOAT;
    static GLType VEC2;
    static GLType VEC3;
    static GLType VEC4;
    static GLType MAT4;

    GLType( uint32 pId, uint32 pNumComps, uint32 pBytesize ) 
        : id(pId), numComps(pNumComps), byteSize(pBytesize)
    {}

    bool operator==( const GLType& o ) const { return id == o.id; }
    bool operator!=( const GLType& o ) const { return !(*this == o); }

    uint32 id;
    uint32 numComps;
    uint32 byteSize;
};

ENGINE_NAMESPACE_END
