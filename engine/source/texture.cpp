// Header
#include "texture.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Texture::Texture()
{

}

bool Texture::operator==(const Texture & o) const
{
    return _id == o._id;
}

bool Texture::operator!=(const Texture & o) const
{
    return !(*this == o);
}

bool Texture::operator<(const Texture & o1) const
{
    return _id < o1._id;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


ENGINE_NAMESPACE_END
