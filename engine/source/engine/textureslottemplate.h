#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "_gl.h"
#include "textureslot.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class TextureSlotTemplate {
public:
    static const TextureSlotTemplate TEXTURE_DIFFUSE;
    static const TextureSlotTemplate TEXTURE_NORMAL;

    TextureSlotTemplate() = default;
    ~TextureSlotTemplate() = default;

    TextureSlot to_textureslot();

    string  name;
    uint32  slot;
    int32   glTextureSlot;

    bool operator<(const TextureSlotTemplate& o1) const { return name == o1.name ? slot < o1.slot : name < o1.name; }
    bool operator==(const TextureSlotTemplate& o) const { return slot == o.slot && name == o.name; }
    bool operator!=(const TextureSlotTemplate& o) const { return !(*this == o); }
};

ENGINE_NAMESPACE_END
