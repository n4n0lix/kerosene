// Header
#include "defaultrenderengine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

DefaultRenderEngine::DefaultRenderEngine() : IRenderEngine()
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

    // IMAGE UTILS
    //////////////
    ImageUtils::load_png("res/textures/dev/128.png");

    // VERTEX LAYOUT
    //////////////////

    shared_ptr<VertexLayout> pcLayout = make_shared<VertexLayout>(Vertex_pc().layout());

    // SHADER
    ///////////
    ostringstream vertexShader;
    vertexShader
        << "out vec4 fs_color;\n"
        << "\n"
        << "void main() {\n"
        << "    gl_Position = vec4(position, 1.0);\n"
        << "    fs_color = color;\n"
        << "}\n";

    ostringstream fragmentShader;
    fragmentShader
        << "in vec4 fs_color;\n"
        << "\n"
        << "out vec4 out_color;\n"
        << "\n"
        << "void main() {\n"
        << "    out_color = fs_color;\n"
        << "}\n";

    _shader = ShaderBuilder()
                        .uniform(Shader::Uni_WVP)
                        .vertexlayout(pcLayout)
                        .vertex(vertexShader.str())
                        .fragment(fragmentShader.str())
                        .build();

    shared_ptr<Material> material = make_shared<Material>(_shader);

    // BATCH
    //////////
    _batch = make_unique<Batch<Vertex_pc>>(material);

    Vector<Vertex_pc> vertices1 = Vector<Vertex_pc>();
    vertices1.add(Vertex_pc(Vector3f(-1, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices1.add(Vertex_pc(Vector3f( 0, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices1.add(Vertex_pc(Vector3f(-.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle1 = _batch->add_vertices(vertices1);

    Vector<Vertex_pc> vertices2 = Vector<Vertex_pc>();
    vertices2.add(Vertex_pc(Vector3f(0, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices2.add(Vertex_pc(Vector3f(1, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices2.add(Vertex_pc(Vector3f(.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle2 = _batch->add_vertices(vertices2);

    Vector<Vertex_pc> vertices3 = Vector<Vertex_pc>();
    vertices3.add(Vertex_pc(Vector3f(-1, 0, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices3.add(Vertex_pc(Vector3f(0, 0, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices3.add(Vertex_pc(Vector3f(-.5, 1, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle3 = _batch->add_vertices(vertices3);

    Vector<Vertex_pc> vertices4 = Vector<Vertex_pc>();
    vertices4.add(Vertex_pc(Vector3f(0,  0, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices4.add(Vertex_pc(Vector3f(1,  0, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices4.add(Vertex_pc(Vector3f(.5, 1, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle4 = _batch->add_vertices(vertices4);

    _batch->add_render_static(_tokenTriangle1);
    _batch->add_render_static(_tokenTriangle2);
    _batch->add_render_static(_tokenTriangle3);
    _batch->add_render_static(_tokenTriangle4);

}

void DefaultRenderEngine::onUpdate()
{
    // #1 Make context current
    _mainWindow->makeCurrent();

    // #2 GL code
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, _mainWindow->getRenderWidth(), _mainWindow->getRenderHeight());

    // Test code
    _batch->render();

    // #3 Render
    _mainWindow->swapBuffers();

    // X# Update GUI
    glfwPollEvents();
}

void DefaultRenderEngine::onShutdown()
{
    glfwTerminate();
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

ENGINE_NAMESPACE_END
