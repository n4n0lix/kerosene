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
                        .vertexlayout(Vertex_pc().layout())
                        .vertex(vertexShader.str())
                        .fragment(fragmentShader.str())
                        .build();

    shared_ptr<Material> material = make_shared<Material>(_shader);

    // BATCH
    //////////
    vector<Vertex_pc> vertices;
    vertices.push_back(Vertex_pc(Vector3f(-1, -1, 0), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices.push_back(Vertex_pc(Vector3f( 1, -1, 0), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices.push_back(Vertex_pc(Vector3f( 0,  1, 0), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));

    _batch = make_unique<Batch<Vertex_pc>>(material);
    _batch->addVertices(vertices);
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
    _batch->render(PrimitiveType::TRIANGLES);

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
    _mainWindow->makeCurrent();
    std::cout << "Using OpenGL Version " << glGetString(GL_VERSION) << std::endl;
}

ENGINE_NAMESPACE_END
