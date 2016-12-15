#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class TextureSlot {
public:
    static const TextureSlot TEXTURE_DIFFUSE;
    static const TextureSlot TEXTURE_NORMAL;

    TextureSlot(string name = string(""), uint32 slot = 0, int32 glTextureSlot = -1, int32 location = -1) :name(name), slot(slot), glTextureSlot(glTextureSlot), location(location) {}

    string  name;
    uint32  slot;
    int32   glTextureSlot;
    int32   location;

    bool operator<(const TextureSlot& o1) const { return name == o1.name ? slot < o1.slot : name < o1.name; }
    bool operator==(const TextureSlot& o) const { return slot == o.slot && name == o.name; }
    bool operator!=(const TextureSlot& o) const { return !(*this == o); }
};

ENGINE_NAMESPACE_END
