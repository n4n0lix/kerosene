#include "stdafx.h"
#include "renderresource.h"

ENGINE_NAMESPACE_BEGIN

void RenderResource::init( RenderEngine& pRE)
{
    on_init( pRE );
    _init = true;
}

void RenderResource::cleanup( RenderEngine& pRE )
{
    on_cleanup( pRE );
    _init = false;
}

bool RenderResource::is_init()
{
    return _init;
}


ENGINE_NAMESPACE_END