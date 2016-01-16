#ifndef IRENDERENGINE
#define IRENDERENGINE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DLL_PUBLIC IRenderEngine
{

public:
    virtual void onStart()      = 0;
    virtual void onUpdate()     = 0;
    virtual void onShutdown()   = 0;

    virtual void setInterpolation(float interpol) = 0;
    virtual bool isExitRequested() = 0;

};

ENGINE_NAMESPACE_END
#endif // IRENDERENGINE

