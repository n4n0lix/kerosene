#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class VertexComponent {
public:
            VertexComponent() = default;
            ~VertexComponent() = default;

    string type;
    string name;
    uint32 position;

    uint32 num_components() const {
        if ( type == string( "float" ) )
            return 1;
        else if ( type == string( "vec2" ) )
            return 2;
        else if ( type == string( "vec3" ) )
            return 3;
        else if ( type == string( "vec4" ) )
            return 4;
        else
            return 0;
    }

    uint32 bytesize() const {
        if ( type == string( "float" ) )
            return 1 * FLOAT_BYTES;
        else if ( type == string( "vec2" ) )
            return 2 * FLOAT_BYTES;
        else if ( type == string( "vec3" ) )
            return 3 * FLOAT_BYTES;
        else if ( type == string( "vec4" ) )
            return 4 * FLOAT_BYTES;
        else
            return 0;
    }

    GLenum gltype() {
        if ( type == string( "float" ) || type == string( "vec2" )
            || type == string( "vec3" ) || type == string( "vec4" ) ) {
            return GL_FLOAT;
        }

        return GL_NONE;
    }

    bool operator==( const VertexComponent& o ) const { return type == o.type && name == o.name && position == o.position; }
    bool operator!=( const VertexComponent& o ) const { return !(*this == o); }
};

ENGINE_NAMESPACE_END

