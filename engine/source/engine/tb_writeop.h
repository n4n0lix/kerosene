#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Internal Includes
#include "_global.h"
#include "buffertoken.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template <class OBJECT>
class TB_WriteOp {
public:    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            TB_WriteOp(uint32 uid, shared_ptr<BufferToken> token, list<OBJECT> objects);
            ~TB_WriteOp() = default;

    uint32                      uid();
    shared_ptr<BufferToken>     token();
    list<OBJECT>              claim_objects();
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    uint32                      _uid;
    shared_ptr<BufferToken>     _token;
    list<OBJECT>              _objects;

};

template<class OBJECT>
TB_WriteOp<OBJECT>::TB_WriteOp(uint32 uid, shared_ptr<BufferToken> token, list<OBJECT> objects)
{
    _uid = uid;
    _token = token;
    _objects = std::move( objects );
}

template<class OBJECT>
uint32 TB_WriteOp<OBJECT>::uid()
{
    return _uid;
}

template<class OBJECT>
shared_ptr<BufferToken> TB_WriteOp<OBJECT>::token()
{
    return _token;
}

template<class OBJECT>
list<OBJECT> TB_WriteOp<OBJECT>::claim_objects()
{
    return std::move( _objects );
}

ENGINE_NAMESPACE_END


