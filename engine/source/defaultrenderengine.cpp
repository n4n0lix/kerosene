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

    ostringstream vertexShader;
    vertexShader
        << "out vec4 fs_color;\n"
        << "\n"
        << "void main() {\n"
        << "    fs_color = vs_color;\n"
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
                        .in(Shader::VAttr_Position)
                        .in(Shader::VAttr_Color)
                        .vertex(vertexShader.str())
                        .fragment(fragmentShader.str())
                        .build();
}

void DefaultRenderEngine::onUpdate()
{
    // #1 Make context current
    _mainWindow->makeCurrent();

    // #2 GL code
    glClearColor(0.2f, 0.8f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
