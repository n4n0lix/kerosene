#ifndef DISABLEDNETWORKENGINE_H
#define DISABLEDNETWORKENGINE_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "inetworkengine.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DLL_PUBLIC DisabledNetworkEngine : public INetworkEngine
{
public:
            explicit DisabledNetworkEngine();

    virtual void onStart();
    virtual void onUpdate();
    virtual void onShutdown();
};

ENGINE_NAMESPACE_END
#endif // DISABLEDNETWORKENGINE_H
