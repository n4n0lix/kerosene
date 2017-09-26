#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

#include "matrix4f.h"
#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class Uniform {
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static const Uniform WORLD_VIEW_PROJ_MATRIX;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            Uniform() :  Uniform("","") { }
            Uniform( string typeName, string varname ) : _glTypeName(typeName), _glVarName( varname ), _glLocation( 0 ) { }
            ~Uniform() = default;

    inline string gl_typename() const {
        return _glTypeName;
    }

    inline string gl_varname() const {
        return _glVarName;
    }

    inline int32 gl_location() const {
        return _glLocation;
    }

    void gl_location( uint32 loc ) {
        _glLocation = loc;
    }

    bool operator<( const Uniform& o1 ) const { return _glVarName == o1._glVarName ? _glTypeName < o1._glTypeName : _glVarName < o1._glVarName; }
    bool operator==( const Uniform& o ) const { return _glTypeName == o._glTypeName && _glVarName == o._glVarName; }
    bool operator!=( const Uniform& o ) const { return !(*this == o); }


private:

    string  _glTypeName;
    string  _glVarName;
    uint32  _glLocation;

};

ENGINE_NAMESPACE_END
