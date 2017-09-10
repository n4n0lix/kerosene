// Header
#include "renderengine.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

RenderEngine::RenderEngine()
{

}

RenderEngine::~RenderEngine()
{
    
}

void RenderEngine::on_start()
{
    if (!glfwInit()) {
        throw new EngineException("Couldn't initialize GLFW!");
    }

    init_context_and_window();

    if (glewInit() != GLEW_OK) {
        throw new EngineException("Couldn't initialize GLEW!");
    }

	setup_builtin_shaders();

	_camera = make_unique<Camera>();
}

void RenderEngine::on_render(list<GameObject*> gameObjects)
{
	// 1# Setup rendering
    _mainWindow->make_current();

	_camera->set_viewport(0, 0, _mainWindow->get_renderwidth(), _mainWindow->get_renderheight());
	_camera->make_current();

	// #2 Update Rendercomponents
	for (GameObject* gameObject : gameObjects) {
		RenderComponent* component = gameObject->get_rendercomponent();

		if (component != nullptr) {
			if (!component->is_initialized())
				component->init(this);

			component->render();
		}
	}

	// #3 Render batches
	list<s_ptr<IBatch>> batches = list<s_ptr<IBatch>>();

	for (pair<w_ptr<Material>, s_ptr<IBatch>> entry : _materialToBatches) {
		if (!batches.contains(entry.second)) {
			batches.add(entry.second);
		}
	}

	for each (s_ptr<IBatch> batch in batches)
		batch->render();

    _mainWindow->swap_buffers();

    // 4# Update GUI
    glfwPollEvents();
}

void RenderEngine::on_shutdown()
{
	// Release OPEN GL Resources
	_builtinShaders.clear();
	_materialToBatches.clear();
	_tokenToBatches.clear();

	glfwTerminate();
}

void RenderEngine::set_interpolation(float interpol)
{
    // TODO Implement
}

GLWindow* RenderEngine::get_window()
{
    return _mainWindow.get();
}

bool RenderEngine::is_exit_requested()
{
    return  _mainWindow->close_requested();
}

void RenderEngine::remove_vertices(s_ptr<VertexToken> token)
{
	s_ptr<IBatch> batch = _tokenToBatches[token];

	if (batch != nullptr) {
		batch->remove_vertices(token);
	}
}

void RenderEngine::add_render(s_ptr<VertexToken> token)
{
	s_ptr<IBatch> batch = _tokenToBatches[token];

	if (batch != nullptr) {
		batch->add_render(token);
	}
}

void RenderEngine::remove_render(s_ptr<VertexToken> token)
{
	s_ptr<IBatch> batch = _tokenToBatches[token];

	if (batch != nullptr) {
		batch->remove_render(token);
	}
}

s_ptr<Texture> RenderEngine::load_static_texture(string filename, TextureOptions options)
{

	// 1# Check if texture is already loaded. TODO: This currently ignores texture options
	w_ptr<Texture> weak = _fileToTextures.get(filename);
	if (!weak.expired()) {
		return weak.lock();
	}

	// 2# Load Texture
	s_ptr<Texture> texture = s_ptr<Texture>( load_texture(filename, options).release() );
	_fileToTextures.put(filename, texture);
	return texture;
}

/**
 * <summary>Simply loads a texture.</summary>  
 * <returns>
 */
owner<Texture> RenderEngine::load_texture(string filename, TextureOptions options)
{
	owner<Image> image;

	if (StringUtils::ends_with(filename, ".png"))
		image = ImageUtils::load_png(filename);
	else
		LOGGER.log(Level::ERROR) << "Unsupported filetype: " << filename << endl;

	return move( make_unique<Texture>(image.get(), options) );
}

s_ptr<Shader> RenderEngine::load_shader(string filename)
{
	s_ptr<Shader> shader;

	// 1# Check if shader is already loaded. TODO: This currently ignores texture options
	w_ptr<Shader> weak = _fileToShader.get(filename);
	if (!weak.expired()) {
		return weak.lock();
	}

	if (shader != nullptr) {
		return shader;
	}

	// 2# Try to load from built-in-shaders
	s_ptr<Shader> builtIn = _builtinShaders.get(filename);
	if (builtIn != nullptr) {
		return builtIn;
	}

	// 3# Load Shader from file
	// TODO:

	LOGGER.log(Level::WARN) << "Shader '" << filename << "' not found!";

	return nullptr;
}

s_ptr<Material> RenderEngine::load_material(s_ptr<Shader> shader, s_ptr<Texture> texture)
{
	return s_ptr<Material>();
}

s_ptr<Shader> RenderEngine::built_in_shader(string filename, s_ptr<Shader> shader)
{
	_builtinShaders.put(filename, shader);
	return shader;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void RenderEngine::init_context_and_window()
{
    _mainWindow = std::make_unique<GLWindow>("Test", 800, 600);
    _mainWindow->set_x(800);
    _mainWindow->set_y(300);
    _mainWindow->make_current();
    std::cout << "Using OpenGL Version " << glGetString(GL_VERSION) << std::endl;
}

void RenderEngine::setup_builtin_shaders()
{
	// VERTEX LAYOUTS
	VertexLayout pcLayout = Vertex_pc().layout();
	VertexLayout ptLayout = Vertex_pt().layout();

	// SETUP BUILT-IN SHADER
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

	s_ptr<Shader> colorShader = ShaderBuilder()
		.vertex_uniform("mat4", "uni_wvp")
		.vertexlayout(pcLayout)
		.vertex_source(csVertexShader.str())
		.frag_source(csFragmentShader.str())
		.build();

	built_in_shader("builtin_diffuse", colorShader);

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
		<< "    out_color = texture(" << TextureSlotTemplate::TEXTURE_DIFFUSE.name << ", fs_texcoords);\n"
		<< "}\n";

	s_ptr<Shader> texShader = ShaderBuilder()
		.vertex_uniform("mat4", "uni_wvp")
		.frag_texture_slot(TextureSlotTemplate::TEXTURE_DIFFUSE)
		.vertexlayout(ptLayout)
		.vertex_source(tsVertexShader.str())
		.frag_source(tsFragmentShader.str())
		.build();

	built_in_shader("builtin_texture", texShader);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger RenderEngine::LOGGER = Logger("RenderEngine", Level::DEBUG);

ENGINE_NAMESPACE_END
