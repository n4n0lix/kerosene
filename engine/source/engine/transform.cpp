#include "transform.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


Transform::Transform() : position(Vector3f::zero()), scale(Vector3f::unit()), rotation(Quaternion4f::rotationIdentity())
{
}

Matrix4f Transform::toMatrix4f()
{
    Matrix4f mat4Scale = Matrix4f::scaling( scale );
    Matrix4f mat4Rot   = Quaternion4f::toRotationMatrix4f( rotation );
    Matrix4f mat4Trans = Matrix4f::translation( position );

    return (mat4Scale * mat4Rot) * mat4Trans;
}

ENGINE_NAMESPACE_END