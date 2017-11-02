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

class VertexBufferToken {

    template<class T>
    friend class VertexBuffer;

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                VertexBufferToken(uint32 id, void* buffer);
                ~VertexBufferToken() = default;

    bool                        valid();            // Returns true as soon as the objects are written in the buffer

    Range                       object_range();
    std::vector<uint32>         object_indices();

    bool                        operator!=(const VertexBufferToken& o) const;
    bool                        operator==(const VertexBufferToken& o) const;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                   Protected (friends)                  */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
protected:

    void*                       get_buffer();
    uint32                      get_id();

    void                        set_range_id(uint32 rangeId);
    uint32                      range_id();

    void                        invalidate();
    void                        validate();

    void                        set_object_size(uint32 objSize);
    uint32                      object_size();

    void                        set_atom_range(Range range);
    Range                       atom_range();

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void                        update();


    uint32          id;
    void*           _buffer;

    bool            _valid;

    uint32                      _rangeId;
    uint32                      _objSize;
    Range                       _atomRange;
    Range                       _objRange;

};

ENGINE_NAMESPACE_END