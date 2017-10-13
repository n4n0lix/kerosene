#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "object.h"
#include "entity.h"
#include "keyevent.h"
#include "charevent.h"
#include "mouseevent.h"
#include "controllable.h"

ENGINE_NAMESPACE_BEGIN

struct LocalController : public Object
{
    virtual void    update( vector<KeyEvent>&, vector<CharEvent>&, vector<MouseEvent>& ) = 0;
};

ENGINE_NAMESPACE_END
