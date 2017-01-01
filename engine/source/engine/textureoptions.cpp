#include "textureoptions.h"

ENGINE_NAMESPACE_BEGIN

TextureOptions::TextureOptions() : _filteringMode(TextureFiltering::NEAREST)
{
}

TextureOptions& TextureOptions::filtering(TextureFiltering filteringMode)
{
    _filteringMode = filteringMode;
    return *this;
}

TextureFiltering TextureOptions::filtering()
{
    return _filteringMode;
}

ENGINE_NAMESPACE_END