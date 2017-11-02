#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes


// Other Includes

// Internal Includes
#include "_global.h"
#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"
#include "quaternion4f.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Helpers                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

union DoubleNetConverter {
    double asDouble;
    uint64 asUInt64;
};


union FloatNetConverter {
    float  asFloat;
    uint32 asUInt32;
};


inline void __net_write( std::vector<byte>& v, bool value ) {
    v.push_back( value );
}


inline void __net_write( std::vector<byte>& v, char value ) {
    v.push_back( value );
}


inline void __net_write( std::vector<byte>& v, int16 value ) {
    v.push_back( (value & 0xFF00) >> 8 );
    v.push_back( (value & 0x00FF) );
}


inline void __net_write( std::vector<byte>& v, uint16 value ) {
    v.push_back( (value & 0xFF00) >> 8 );
    v.push_back( (value & 0x00FF) );
}


inline void __net_write( std::vector<byte>& v, int32 value ) {
    v.push_back( (value & 0xFF000000) >> 24 );
    v.push_back( (value & 0x00FF0000) >> 16 );
    v.push_back( (value & 0x0000FF00) >> 8 );
    v.push_back( (value & 0x000000FF) );
}


inline void __net_write( std::vector<byte>& v, uint32 value ) {
    v.push_back( (value & 0xFF000000) >> 24 );
    v.push_back( (value & 0x00FF0000) >> 16 );
    v.push_back( (value & 0x0000FF00) >> 8 );
    v.push_back( (value & 0x000000FF) );
}


inline void __net_write( std::vector<byte>& v, float value ) {
    FloatNetConverter val;
    val.asFloat = value;
    __net_write( v, val.asUInt32 );
}


inline void __net_write( std::vector<byte>& v, Vector2f value ) {
    __net_write( v, value.x );
    __net_write( v, value.y );
}


inline void __net_write( std::vector<byte>& v, Vector3f value ) {
    __net_write( v, value.x );
    __net_write( v, value.y );
    __net_write( v, value.z );
}


inline void __net_write( std::vector<byte>& v, Vector4f value ) {
    __net_write( v, value.x );
    __net_write( v, value.y );
    __net_write( v, value.z );
    __net_write( v, value.w );
}


inline void __net_write( std::vector<byte>& v, Quaternion4f value ) {
    __net_write( v, value.x );
    __net_write( v, value.y );
    __net_write( v, value.z );
    __net_write( v, value.w );
}

inline void __net_write( std::vector<byte>& v, string str ) {
    uint16 length = (uint16)std::min( str.length(), size_t( 1024 ) ); // 1024 - Max String Length for net packets
    __net_write( v, length );

    for ( auto chr : str.substr( 0, length - 1 ) ) {
        __net_write( v, chr );
    }
}

enum class NetVarType {
    SHARED,
    SELF,
    SERVER
};

enum class NetVarID {
    Entity_uid          = 0,    // SHARED
    Entity_transform    = 1,    // SHARED

    Creature_health     = 64,   // SHARED
    Creature_name       = 65,   // SHARED
    Creature_stamina    = 66    // SELF
};
ENGINE_NAMESPACE_END
