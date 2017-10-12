#include "stdafx.h"
#include "textureslot.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Public                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const TextureSlot TextureSlot::TEXTURE_DIFFUSE = { "tex_diffuse",    0, GL_TEXTURE0 };
const TextureSlot TextureSlot::TEXTURE_NORMAL  = { "tex_normal",     1, GL_TEXTURE1 };

ENGINE_NAMESPACE_END


