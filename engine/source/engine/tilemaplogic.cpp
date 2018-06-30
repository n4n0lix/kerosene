#include "stdafx.h"
#include "tilemaplogic.h"

ENGINE_NAMESPACE_BEGIN

void CTilemapLogic::update(float delta) 
{

}

void CTilemapLogic::reshape(uint32 pWidth, uint32 pHeight) {
  width = pWidth;
  height = pHeight;

  tiles.resize(height * width, 0);
}

void CTilemapLogic::set_tile(uint32 x, uint32 y, uint32 tile) {
  tiles[y * width + x] = tile;
}

int  CTilemapLogic::get_tile(uint32 x, uint32 y) {
  return tiles[y * width + x];
}

ENGINE_NAMESPACE_END
