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

    shared_ptr<vector<Vertex_pc>> vertices1 = make_shared<vector<Vertex_pc>>();
    vertices1->push_back(Vertex_pc(Vector3f(-1, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices1->push_back(Vertex_pc(Vector3f( 0, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices1->push_back(Vertex_pc(Vector3f(-.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle1 = _batch->addVertices(vertices1);

    shared_ptr<vector<Vertex_pc>> vertices2 = make_shared<vector<Vertex_pc>>();
    vertices2->push_back(Vertex_pc(Vector3f(0, -1, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices2->push_back(Vertex_pc(Vector3f(1, -1, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    vertices2->push_back(Vertex_pc(Vector3f(.5, 0, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    _tokenTriangle2 = _batch->addVertices(vertices2);

    //shared_ptr<vector<Vertex_pc>> vertices3 = make_shared<vector<Vertex_pc>>();
    //vertices3->push_back(Vertex_pc(Vector3f(-1, 0, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    //vertices3->push_back(Vertex_pc(Vector3f(0, 0, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    //vertices3->push_back(Vertex_pc(Vector3f(-.5, 1, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    //_tokenTriangle3 = _batch->addVertices(vertices3);

    //shared_ptr<vector<Vertex_pc>> vertices4 = make_shared<vector<Vertex_pc>>();
    //vertices4->push_back(Vertex_pc(Vector3f(0,  0, -.5), Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
    //vertices4->push_back(Vertex_pc(Vector3f(1,  0, -.5), Vector4f(1.0f, 1.0f, 0.0f, 1.0f)));
    //vertices4->push_back(Vertex_pc(Vector3f(.5, 1, -.5), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
    //_tokenTriangle4 = _batch->addVertices(vertices4);

    shared_ptr<vector<uint32>> indices = make_shared<vector<uint32>>();
    indices->push_back(0);
    indices->push_back(1);
    indices->push_back(2);
    indices->push_back(3);
    indices->push_back(4);
    indices->push_back(5);
    _batch->addIndices(indices);
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
    _batch->render(_tokenTriangle1);
    //_batch->render(_tokenTriangle2);
    //_batch->render(_tokenTriangle3);
    //_batch->render(_tokenTriangle4);
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
