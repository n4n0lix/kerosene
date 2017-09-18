#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"

#include "range.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class StackBufferToken {

    template<class T>
    friend class StackBuffer;

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            StackBufferToken( uint32 id, void* buffer );
            virtual ~StackBufferToken() = default;


    bool                        valid();
    Range                       object_range();
    vector<uint32>              object_indices();

    bool                        operator!=( const StackBufferToken& o ) const;
    bool                        operator==( const StackBufferToken& o ) const;

protected:

    uint32                      range_id();
    void                        set_range_id( uint32 rangeId );

    void*                       get_buffer();
    uint32                      get_id();

    void                        invalidate();
    void                        validate();

    void                        set_object_size( uint32 objSize );
    uint32                      object_size();

    void                        set_atom_range( Range range );
    Range                       atom_range();
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    uint32 _rangeId;

    void                        update();

    void*   _buffer;
    uint32  _id;

    bool    _valid;

    uint32                      _objSize;
    Range                       _atomRange;
    Range                       _objRange;

};

ENGINE_NAMESPACE_END