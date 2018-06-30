#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "transform.h"
#include "vector2f.h"
#include "stopwatch.h"
#include "component.h"

ENGINE_NAMESPACE_BEGIN

COMPONENT( CTilemapLogic, 10) 

  void update(float delta) override;

  void reshape(uint32 pWidth, uint32 pHeight);
  void set_tile(uint32 x, uint32 y, uint32 tile);
  int  get_tile(uint32 x, uint32 y);

  GLOBAL:
    uint32 width;
    uint32 height;
    float  tileWidth;
    float  tileHeight;
    std::vector<uint32> tiles;

  PLAYER:

  LOCAL:

END

ENGINE_NAMESPACE_END
