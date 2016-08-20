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

    // TEXTURE 
    //////////////
    shared_ptr<Image> img = ImageUtils::load_png("res/textures/dev/128.png");
    _tex = make_shared<Texture>( img, false );

    // VERTEX LAYOUT
    //////////////////

    shared_ptr<VertexLayout> pcLayout = make_shared<VertexLayout>(Vertex_pc().layout());
    shared_ptr<VertexLayout> ptLayout = make_shared<VertexLayout>(Vertex_pt().layout());

    // COLOR SHADER
    ///////////
    ostringstream csVertexShader;
    csVertexShader
        << "out vec4 fs_color;\n"
        << "\n"
        << "void main() {\n"
        << "    gl_Position = vec4(position, 1.0);\n"
        << "    fs_color = color;\n"
        << "}\n";

    ostringstream csFragmentShader;
    csFragmentShader
        << "in vec4 fs_color;\n"
        << "\n"
        << "out vec4 out_color;\n"
        << "\n"
        << "void main() {\n"
        << "    out_color = fs_color;\n"
        << "}\n";

    shared_ptr<Shader> colorShader = ShaderBuilder()
                        .vertex_uniform({ "mat4", "uni_wvp" })
                        .vertexlayout(pcLayout)
                        .vertex_source(csVertexShader.str())
                        .frag_source(csFragmentShader.str())
                        .build();

    shared_ptr<Material> materialColor = make_shared<Material>( colorShader );

    // TEXTURE SHADER
    ///////////
    ostringstream tsVertexShader;
    tsVertexShader
        << "out vec2 fs_texcoords;\n"
        << "\n"
        << "void main() {\n"
        << "    gl_Position = vec4(position, 1.0);\n"
        << "    fs_texcoords = texcoords;\n"
        << "}\n";

    ostringstream tsFragmentShader;
    tsFragmentShader
        << "in vec2 fs_texcoords;\n"
        << "\n"
        << "out vec4 out_color;\n"
        << "\n"
        << "void main() {\n"
        << "    out_color = texture(texture_base, fs_texcoords);\n"
        << "}\n";

    shared_ptr<Shader> texShader = ShaderBuilder()
        .vertex_uniform({ "mat4",       "uni_wvp" })
        .frag_uniform({ "sampler2D",  "texture_base" })
        .vertexlayout(ptLayout)
        .vertex_source(tsVertexShader.str())
        .frag_source(tsFragmentShader.str())
        .build();

    shared_ptr<Material> materialTex = make_shared<Material>(texShader, _tex);

    // BATCH
    //////////
    _batch = make_unique<Batch<Vertex_pc>>(materialColor);

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

    _batch->add_render_static(_tokenTriangle1);
    _batch->add_render_static(_tokenTriangle2);
    _batch->add_render_static(_tokenTriangle3);

    // BATCH 2
    //////////
    _batch2 = make_unique<Batch<Vertex_pt>>(materialTex);

    Vector<Vertex_pt> vertices4 = Vector<Vertex_pt>();
    vertices4.add(Vertex_pt(Vector3f(1, 0, -.5), Vector2f(1.0f, 1.0f)));
    vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
    vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));

    vertices4.add(Vertex_pt(Vector3f(0, 0, -.5), Vector2f(0.0f, 1.0f)));
    vertices4.add(Vertex_pt(Vector3f(1, 1, -.5), Vector2f(1.0f, 0.0f)));
    vertices4.add(Vertex_pt(Vector3f(0, 1, -.5), Vector2f(0.0f, 0.0f)));

    _tokenTriangle4 = _batch2->add_vertices(vertices4);
    _batch2->add_render_static(_tokenTriangle4);

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
    _batch2->render();

    // #3 Render
    _mainWindow->swapBuffers();

    // X# Update GUI
    glfwPollEvents();
}

void DefaultRenderEngine::onShutdown()
{
    // TODO: Fix this, should be deleted automatically by destructor of texture
    GLuint texId = _tex->id();
    glDeleteTextures(1, &texId);

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
