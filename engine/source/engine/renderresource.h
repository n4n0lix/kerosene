#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "noncopyable.h"
#include "renderengine.h"
#include "logger.h"

ENGINE_NAMESPACE_BEGIN

class RenderEngine;

class RenderResource : public noncopyable
{
public:
    RenderResource() = default;
    virtual ~RenderResource() = default;

    void init( RenderEngine& );
    void cleanup( RenderEngine& );

    bool is_init();

    virtual void        on_init( RenderEngine& ) = 0;
    virtual void        on_cleanup( RenderEngine& ) = 0;

private:
    bool _init;
};

ENGINE_NAMESPACE_END
