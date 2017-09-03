#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Std-Extensions
#include "list.h"

// Internal Includes
#include "_global.h"
#include "range.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class BufferToken {
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                BufferToken(uint32 id, void* buffer);

    void*                       get_buffer();
    uint32                      get_id();

    bool                        valid();            // Returns true as soon as the objects are written in the buffer
    Range                       atom_range();
    Range                       object_range();
    uint32                      object_size();
    list<uint32>                object_indices();

    void                        move(uint32 distance);

    void                        invalidate();
    void                        validate();
    void                        set_object_size(uint32 objSize);
    void                        set_atom_range(Range range);

    bool                        operator!=(const BufferToken& o) const;
    bool                        operator==(const BufferToken& o) const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                        update();

    void*  _buffer;
    uint32 _id;

    bool   _valid;

    uint32                      _objSize;
    Range                       _atomRange;
    Range                       _objRange;
    shared_ptr<vector<uint32>>  _objIndices;
};

ENGINE_NAMESPACE_END

