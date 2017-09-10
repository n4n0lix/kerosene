#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"
#include "list.h"
#include "range.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class VertexBufferToken {
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                VertexBufferToken(uint32 id, void* buffer);

    uint32      range_id();
    void        set_range_id(uint32 rangeId);

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

    bool                        operator!=(const VertexBufferToken& o) const;
    bool                        operator==(const VertexBufferToken& o) const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                        update();


    uint32          _id;
    void*           _buffer;

    bool            _valid;

    uint32                      _rangeId;
    uint32                      _objSize;
    Range                       _atomRange;
    Range                       _objRange;
    shared_ptr<vector<uint32>>  _objIndices;

};

ENGINE_NAMESPACE_END