#include "stdafx.h"
#include "tilemaplogic.h"

ENGINE_NAMESPACE_BEGIN

REGISTER_MIXIN( 2, TilemapLogic )

void TilemapLogic::reshape( uint32 pWidth, uint32 pHeight ) {
    width = pWidth;
    height = pHeight;

    tiles.resize( height * width, 0 );
}

void TilemapLogic::set_tile( uint32 x, uint32 y, uint32 tile ) {
    tiles[y * width + x] = tile;
}

int  TilemapLogic::get_tile( uint32 x, uint32 y ) {
    return tiles[y * width + x];
}

ENGINE_NAMESPACE_END
