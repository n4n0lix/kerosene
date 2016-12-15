// Header
#include "textureslottemplate.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const TextureSlotTemplate TextureSlotTemplate::TEXTURE_DIFFUSE = { "tex_diffuse",    0, GL_TEXTURE0 };
const TextureSlotTemplate TextureSlotTemplate::TEXTURE_NORMAL  = { "texture_normal", 1, GL_TEXTURE1 };

TextureSlot TextureSlotTemplate::to_textureslot()
{
    return TextureSlot(name, slot, glTextureSlot);
}

ENGINE_NAMESPACE_END


