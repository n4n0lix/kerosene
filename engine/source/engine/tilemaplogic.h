#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "mixins.h"
#include "transform.h"
#include "vector2f.h"

ENGINE_NAMESPACE_BEGIN

struct TilemapLogic : mixin::Mixin
{
    void reshape( uint32 tileWidth, uint32 tileHeight );
    void set_tile( uint32 x, uint32 y, uint32 tile );
    int  get_tile( uint32 x, uint32 y );

GLOBAL:

PLAYER:

LOCAL:
    uint32 width;
    uint32 height;
    float  tileWidth;
    float  tileHeight;

    std::vector<uint32> tiles;
};


DEFINE_MIXIN( TilemapLogic );

ENGINE_NAMESPACE_END
