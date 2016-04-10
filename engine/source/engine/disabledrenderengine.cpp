// Header
#include "disabledrenderengine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

DisabledRenderEngine::DisabledRenderEngine() : IRenderEngine()
{

}

void DisabledRenderEngine::onStart()
{

}

void DisabledRenderEngine::onUpdate()
{

}

void DisabledRenderEngine::onShutdown()
{

}

void DisabledRenderEngine::setInterpolation(float interpol)
{

}

bool DisabledRenderEngine::isExitRequested() {
    return false;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
