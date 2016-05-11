#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes


// Internal Includes
#include "_global.h"

#include "buffer.h"
#include "bufferrange.h"

#include "tb_writeop.h"
#include "tb_removeop.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<class T>
class TransactionalBuffer : public Buffer<T>
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                            TransactionalBuffer(uint32 objSize, uint32 objCapacity);


            void                            commit();

    virtual uint32                          num_objects();

    virtual shared_ptr<BufferToken>         write(shared_ptr<vector<T>> objects);
    virtual void                            remove(shared_ptr<BufferToken> token);
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            uint32                          generate_token_id();
    const   Vector<shared_ptr<TB_Token>>&   get_active_tokens();

    virtual TB_Token                        create_token(); // Override this if custom token class is used

    // Inter-Implementation
    virtual void                            commit_write(shared_ptr<vector<T>> objects, shared_ptr<TB_Token> commit_token) = 0;
    virtual void                            commit_remove(shared_ptr<TB_Token> token) = 0;

    // Final-Implementation
    virtual void                            write(uint32 index, shared_ptr<vector<T>> objects) = 0;
    virtual void                            remove(uint32 index, uint32 length) = 0;
    virtual void                            resize(uint32 oldCapacity, uint32 newCapacity) = 0;


private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            uint32                          generate_writeop_id();
            uint32                          generate_removeop_id();

    uint32                                  _numObjects;

    Vector<shared_ptr<TB_WriteOp<T>>>       _writeBucket;
    Vector<shared_ptr<TB_RemoveOp>>         _removeBucket;
    Vector<shared_ptr<TB_Token>>            _activeTokens;

    uint32                  _nextUidToken;
    uint32                  _nextUidWriteOp;
    uint32                  _nextUidRemoveOp;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
TransactionalBuffer<T>::TransactionalBuffer(uint32 objSize, uint32 objCapacity) : Buffer(objSize, objCapacity)
{
    _nextUidToken = TB_Token::FIRST_UID;
    _nextUidWriteOp  = TB_WriteOp<T>::FIRST_UID;
    _nextUidRemoveOp = TB_RemoveOp::FIRST_UID;

    _numObjects = 0;
}

template<class T>
shared_ptr<BufferToken> TransactionalBuffer<T>::write(shared_ptr<vector<T>> objects)
{
    // 1# Create token
    shared_ptr<TB_Token> token = make_shared<TB_Token>(generate_token_id(), this);

    // 2# Store in write bucket
    _writeBucket.add(make_shared<TB_WriteOp<T>>(generate_writeop_id(), token, objects));
    _activeTokens.add(token);

    // 3# Return token
    return dynamic_pointer_cast<BufferToken>(token);
}

template<class T>
void TransactionalBuffer<T>::remove(shared_ptr<BufferToken> bufferToken)
{
    // 1# Only accept TB_Token
    shared_ptr<TB_Token> token;

    if (!(token = static_pointer_cast<TB_Token>(bufferToken))) {
        LOGGER.log(Level::WARN) << "Invalid token received, not of class TB_Token!" << endl;
        return;
    }

    // 2# Check if token is invalid, and remove corresponding writeops ...
    if (!token->valid()) {
        _writeBucket.remove([&](shared_ptr<TB_WriteOp<T>> op) -> bool { return op->token() == token; });
        return;
    }

    // 3# Create RemoveOp for token
    _removeBucket.add(make_shared<TB_RemoveOp>(generate_removeop_id(), token));
}

template<class T>
TB_Token TransactionalBuffer<T>::create_token()
{
    return TB_Token(generate_token_id(), this);
}

template<class T>
void TransactionalBuffer<T>::commit() {
    // 1# Do RemoveOps
    for (auto removeOp : _removeBucket) {
        auto removeToken = removeOp->token();
        commit_remove(removeToken);
        _numObjects -= removeToken->object_length();
    }
    _removeBucket.clear();

    // 2# Do WriteOps
    for (auto writeOp : _writeBucket) {
        auto writeToken = writeOp->token();
        commit_write(writeOp->objects(), writeToken);
        _numObjects += writeToken->object_length();
    }
    _writeBucket.clear();
}

template<class T>
uint32 TransactionalBuffer<T>::num_objects()
{
    return _numObjects;
}

template<class T>
uint32 TransactionalBuffer<T>::generate_token_id() {
    return _nextUidToken++;
}

template<class T>
const Vector<shared_ptr<TB_Token>>& TransactionalBuffer<T>::get_active_tokens()
{
    return _activeTokens;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
uint32 TransactionalBuffer<T>::generate_writeop_id() {
    return _nextUidWriteOp++;
}

template<class T>
uint32 TransactionalBuffer<T>::generate_removeop_id() {
    return _nextUidRemoveOp++;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class OBJECT>
Logger TransactionalBuffer<OBJECT>::LOGGER = Logger("TransactionalBuffer<>", Level::DEBUG);

ENGINE_NAMESPACE_END