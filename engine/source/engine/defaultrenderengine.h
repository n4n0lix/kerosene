#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "engineexception.h"
#include "irenderengine.h"
#include "glwindow.h"

// Testing Includes (temporary)
#include "shader.h"
#include "shaderbuilder.h"
#include "batch.h"
#include "vertex_pc.h"
#include "primitivetype.h"
#include "vertexarray.h"
#include "imageutils.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DefaultRenderEngine : public IRenderEngine
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
    unique_ptr<Batch<Vertex_pc>> _batch;
    unique_ptr<VertexArray<Vertex_pc>> _vao;

    shared_ptr<VertexToken> _tokenTriangle1;
    shared_ptr<VertexToken> _tokenTriangle2;
    shared_ptr<VertexToken> _tokenTriangle3;
    shared_ptr<VertexToken> _tokenTriangle4;
};

ENGINE_NAMESPACE_END
