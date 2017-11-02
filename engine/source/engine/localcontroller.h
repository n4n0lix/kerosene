#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "noncopyable.h"
#include "entity.h"
#include "keyevent.h"
#include "charevent.h"
#include "mouseevent.h"
#include "controllable.h"

ENGINE_NAMESPACE_BEGIN

struct LocalController : public noncopyable
{
    virtual void    update( std::vector<KeyEvent>&, std::vector<CharEvent>&, std::vector<MouseEvent>& ) = 0;
};

ENGINE_NAMESPACE_END
