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

template<class OBJECT, class TOKEN>
class TransactionBucket
{
    typedef function<void(TOKEN, Vector<OBJECT>*)>  WriteFunc;
    typedef function<void(TOKEN)>                   RemoveFunc;

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                    TransactionBucket();
                    TransactionBucket(WriteFunc writeFunc, RemoveFunc removeFunc);

    void            commit();

    void            write (TOKEN token, Vector<OBJECT>* objects);
    void            remove(TOKEN token);
protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    map<TOKEN, Vector<OBJECT>*>     _writeBucket;
    Vector<TOKEN>                   _removeBucket;

    WriteFunc  _writeFunc;
    RemoveFunc _removeFunc;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Private                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class OBJ, class TOKEN>
TransactionBucket<OBJ, TOKEN>::TransactionBucket() { }

template<class OBJ, class TOKEN>
TransactionBucket<OBJ, TOKEN>::TransactionBucket(WriteFunc writeFunc, RemoveFunc removeFunc)
{
    _writeFunc = writeFunc;
    _removeFunc = removeFunc;
}

template<class OBJ, class TOKEN>
void TransactionBucket<OBJ, TOKEN>::commit()
{
    // 1# Remove
    for (auto token : _removeBucket) {
        _removeFunc(token);
    }
    _removeBucket.clear();

    // 2# Write
    for (auto entry : _writeBucket) {
        _writeFunc(entry.first, entry.second);
    }
    _writeBucket.clear();
}

template<class OBJ, class TOKEN>
void TransactionBucket<OBJ, TOKEN>::write(TOKEN token, Vector<OBJ>* objects)
{
    _writeBucket[token] = objects;
}

template<class OBJ, class TOKEN>
void TransactionBucket<OBJ, TOKEN>::remove(TOKEN token)
{
    _removeBucket.add(token);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
