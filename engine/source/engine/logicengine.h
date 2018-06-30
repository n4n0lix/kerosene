#pragma once

// Std-Includes
#include <exception>

// Other Includes

// Internal Includes
#include "_global.h"
#include "idgen.h"

#include "entity.h"
#include "transform.h"
#include "controllable.h"
#include "component.h"
#include "tilemaplogic.h"

ENGINE_NAMESPACE_BEGIN

class LogicEngine
{
public:
    void on_start();
    void on_tick_start();
    void on_update(float delta);
    void on_shutdown();

    void on_gamestate_end();
};

ENGINE_NAMESPACE_END

