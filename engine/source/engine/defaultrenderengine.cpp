// Header
#include "defaultrenderengine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

DefaultRenderEngine::DefaultRenderEngine() : IRenderEngine()
{

}



DefaultRenderEngine::~DefaultRenderEngine()
{
    //glfwTerminate();
}

void DefaultRenderEngine::cleanUp()
{

}

void DefaultRenderEngine::onStart()
{
    _exitRequested = false; 

    if (!glfwInit()) {
        throw new EngineException("Couldn't initialize GLFW!");
    }

    initContextAndWindow();

    if (glewInit() != GLEW_OK) {
        throw new EngineException("Couldn't initialize GLEW!");
    }

    // RENDER MANAGER
    //////////////
    _world = make_shared<World>();
    _renderManagers.put( _world, make_shared<RenderManager>() );

    s_ptr<RenderManager> renderManagerW1 = _renderManagers.get( _world );
    // MATERIALS 
    //////////////
    s_ptr<Shader> shad = renderManagerW1->load_shader("builtin_texture");

    s_ptr<Material> matTex = make_shared<Material>( renderManagerW1->load_shader("builtin_texture"),
                                                    renderManagerW1->load_texture("res/textures/dev/128.png") );

    s_ptr<Material> matColor = make_shared<Material>( renderManagerW1->load_shader("builtin_diffuse") );

    // BATCH
    //////////
    Vector<Vertex_pc> vertices1 = Vector<Vertex_pc>();
    vertices1.add(Vertex_pc(Vector3f(-1, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices1.add(Vertex_pc(Vector3f( 0, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices1.add(Vertex_pc(Vector3f(-.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle1 = renderManagerW1->add_vertices(matColor, vertices1);

    Vector<Vertex_pc> vertices2 = Vector<Vertex_pc>();
    vertices2.add(Vertex_pc(Vector3f(0, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices2.add(Vertex_pc(Vector3f(1, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices2.add(Vertex_pc(Vector3f(.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle2 = renderManagerW1->add_vertices(matColor, vertices2);

    Vector<Vertex_pc> vertices3 = Vector<Vertex_pc>();
    vertices3.add(Vertex_pc(Vector3f(-1, 0, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices3.add(Vertex_pc(Vector3f(0, 0, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices3.add(Vertex_pc(Vector3f(-.5, 1, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle3 = renderManagerW1->add_vertices(matColor, vertices3);

    renderManagerW1->add_render( _tokenTriangle1 );
    renderManagerW1->add_render( _tokenTriangle2 );
    renderManagerW1->add_render( _tokenTriangle3 );

    // BATCH 2
    //////////
    Vector<Vertex_pt> vertices4 = Vector<Vertex_pt>();
    vertices4.add(Vertex_pt(Vector3f(1, 0, -.5), Vector2f(1.0f, 1.0f)));
    vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
    vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));

    vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
    vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));
    vertices4.add(Vertex_pt(Vector3f(0, 1, -.5), Vector2f(0.0f, 0.0f)));

    _tokenTriangle4 = renderManagerW1->add_vertices(matTex, vertices4);
    renderManagerW1->add_render(_tokenTriangle4);

    // CAMERA
    ///////////
    _camera = make_unique<Camera>();
}

void DefaultRenderEngine::onUpdate()
{
    // #1 Make context current
    _mainWindow->makeCurrent();

    // #2 Render
    _camera->set_viewport(0, 0, _mainWindow->getRenderWidth(), _mainWindow->getRenderHeight());
    _renderManagers.get( _world )->render();
    _mainWindow->swapBuffers();

    // X# Update GUI
    glfwPollEvents();
}

void DefaultRenderEngine::onShutdown()
{

}

void DefaultRenderEngine::setInterpolation(float interpol)
{
    // TODO Implement
}

bool DefaultRenderEngine::isExitRequested()
{
    return _exitRequested || _mainWindow->closeRequested();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DefaultRenderEngine::initContextAndWindow()
{
    _mainWindow = std::make_unique<GLWindow>("Test", 800, 600);
    _mainWindow->setX(800);
    _mainWindow->setY(300);
    _mainWindow->makeCurrent();
    std::cout << "Using OpenGL Version " << glGetString(GL_VERSION) << std::endl;
}


void DefaultRenderEngine::setup_built_in_shaders()
{

}

ENGINE_NAMESPACE_END
