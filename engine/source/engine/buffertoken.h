#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"

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

    bool                        valid();
    uint32                      atom_index();
    uint32                      atom_length();
    uint32                      object_index();
    uint32                      object_length();
    uint32                      object_size();
    shared_ptr<vector<uint32>>  object_indices();

    void                        invalidate();
    void                        validate();
    void                        set_data(uint32 atomIndex, uint32 atomLength, uint32 objSize);

    bool                        operator!=(const BufferToken& o) const;
    bool                        operator==(const BufferToken& o) const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    void*  _buffer;
    uint32 _id;

    bool   _valid;

    uint32                      _atomIndex;
    uint32                      _atomLength;
    uint32                      _objIndex;
    uint32                      _objLength;
    shared_ptr<vector<uint32>>  _objIndices;
};

ENGINE_NAMESPACE_END

