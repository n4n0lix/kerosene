#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

#include "vector3f.h"
#include "quaternion4f.h"
#include "matrix4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class Transform
{
public:
    static inline Transform lerp( const Transform& pTrans0, const Transform& pTrans1, float pLerpAmount )
    {
        Transform result;
        result.position = Vector3f::lerp( pTrans0.position, pTrans1.position, pLerpAmount );
        result.scale    = Vector3f::lerp( pTrans0.scale, pTrans1.scale, pLerpAmount );
        result.rotation = Quaternion4f::slerp( pTrans0.rotation, pTrans1.rotation, pLerpAmount );
        return result;
    }


    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            Transform();
            ~Transform() = default;

    Matrix4f    to_mat4f();

    Vector3f        position;
    Vector3f        scale;
    Quaternion4f    rotation;

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

ENGINE_NAMESPACE_END
