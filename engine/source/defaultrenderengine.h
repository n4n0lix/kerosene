#ifndef RENDERENGINE_H
#define RENDERENGINE_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>

// Other Includes
#include "glew.h"
#include "glfw3.h"

// Internal Includes
#include "_global.h"
#include "engineexception.h"
#include "irenderengine.h"
#include "glwindow.h"
#include "shader.h"
#include "shaderbuilder.h"
#include "batch.h"
#include "vertex_pc.h"
#include "primitivetype.h"



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DLL_PUBLIC DefaultRenderEngine : public IRenderEngine
{
public:

    const int32_t GL_VERSION_MAJOR = 3;
    const int32_t GL_VERSION_MINOR = 3;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            explicit DefaultRenderEngine();

    /* IRenderEngine */
    virtual void onStart();
    virtual void onUpdate();
    virtual void onShutdown();

    virtual void setInterpolation(float interpol);
    virtual bool isExitRequested();

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    void initContextAndWindow();

    bool                    _exitRequested;
    unique_ptr<GLWindow>    _mainWindow;

    // Test
    shared_ptr<Shader> _shader;
    unique_ptr<Batch> _batch;
};

ENGINE_NAMESPACE_END
#endif // RENDERENGINE_H
