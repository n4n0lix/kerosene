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
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static const uint32 NULL_UID = 0;
    static const uint32 FIRST_UID = 1;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            TB_WriteOp(uint32 uid, shared_ptr<BufferToken> token, shared_ptr<Vector<OBJECT>> objects);

    uint32                      uid();
    shared_ptr<BufferToken>     token();
    shared_ptr<Vector<OBJECT>>  objects();
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    uint32                      _uid;
    shared_ptr<BufferToken>     _token;
    shared_ptr<Vector<OBJECT>>  _objects;

};

template<class OBJECT>
TB_WriteOp<OBJECT>::TB_WriteOp(uint32 uid, shared_ptr<BufferToken> token, shared_ptr<Vector<OBJECT>> objects)
{
    _uid = uid;
    _token = token;
    _objects = objects;
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
shared_ptr<Vector<OBJECT>> TB_WriteOp<OBJECT>::objects()
{
    return _objects;
}

ENGINE_NAMESPACE_END


