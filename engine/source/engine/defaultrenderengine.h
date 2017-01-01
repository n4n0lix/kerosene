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
#include "vertex_pt.h"
#include "primitivetype.h"
#include "vertexarray.h"
#include "imageutils.h"
#include "camera.h"
#include "texture.h"
#include "rendermanager.h"

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
            ~DefaultRenderEngine();

    void cleanUp();

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
    void setup_built_in_shaders();

    bool                    _exitRequested;
    unique_ptr<GLWindow>    _mainWindow;

    shared_ptr<World>                       _world;
    Map<s_ptr<World>, s_ptr<RenderManager>> _renderManagers;

    // Test
    unique_ptr<Camera> _camera;
    unique_ptr<Batch<Vertex_pc>> _batch;
    unique_ptr<Batch<Vertex_pt>> _batch2;
    unique_ptr<VertexArray<Vertex_pc>> _vao;

    shared_ptr<VertexToken> _tokenTriangle1;
    shared_ptr<VertexToken> _tokenTriangle2;
    shared_ptr<VertexToken> _tokenTriangle3;
    shared_ptr<VertexToken> _tokenTriangle4;
};

ENGINE_NAMESPACE_END
