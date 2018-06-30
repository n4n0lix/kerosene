#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes


// Other Includes

// Internal Includes
#include "_global.h"
#include "nethelper.h"

#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"
#include "quaternion4f.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class NetworkVariable {
public:
    uint32 _id;
    virtual void write( std::vector<byte>& ) = 0;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<typename T>
class BaseNetVar : public NetworkVariable {
public:
    BaseNetVar(T t) : value(t) {}
    virtual ~BaseNetVar() = default;

    template<typename T>
    inline BaseNetVar& operator=( const T& other ) { 
        value = other; 
        return *this;
    }

    virtual void write( std::vector<byte>& ) = 0;


    T      value;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<typename T> class NetVar : public BaseNetVar<T> {};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<>
class NetVar<bool> : public BaseNetVar<bool> {
public:
    NetVar( bool aBool ) : BaseNetVar( aBool ) {}

    virtual void write( std::vector<byte>& v )
    {
        __net_write( v, _id );
        __net_write( v, value );
    }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<>
class NetVar<uint32> : public BaseNetVar<uint32> {
public:
    NetVar( uint32 aUint ) : BaseNetVar( aUint ) {}

    virtual void write( std::vector<byte>& v ) override
    {
        __net_write( v, _id );
        __net_write( v, value );
    };
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<>
class NetVar<int32> : public BaseNetVar<int32> {
public:
    NetVar( int32 aInt ) : BaseNetVar( aInt ) {}

    virtual void write( std::vector<byte>& v ) override
    {
        __net_write( v, _id );
        __net_write( v, value );
    };
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<>
class NetVar<string> : public BaseNetVar<string> {
public:
    NetVar( string aString ) : BaseNetVar( aString ) {}

    virtual void write( std::vector<byte>& v ) override
    {
        uint16 length = (uint16)std::min( value.length(), size_t( 1024 ) ); // 1024 - Max String Length for net packets

        __net_write( v, _id );
        __net_write( v, length );

        for ( auto chr : value.substr( 0, length - 1 ) ) {
            __net_write( v, chr );
        }
    };
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<>
class NetVar<Vector3f> : public BaseNetVar<Vector3f> {
public:
    NetVar( Vector3f aVec3 ) : BaseNetVar( aVec3 ) {}

    virtual void write( std::vector<byte>& v ) override {
        __net_write( v, _id );
        __net_write( v, value.x );
        __net_write( v, value.y );
        __net_write( v, value.z );
    };
};

ENGINE_NAMESPACE_END
