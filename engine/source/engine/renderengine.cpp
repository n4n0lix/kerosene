// Header
#include "renderengine.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void RenderEngine::on_start()
{
    if (!glfwInit()) {
        throw std::exception("Couldn't initialize GLFW!");
    }

    init_context_and_window();

    if (glewInit() != GLEW_OK) {
        throw std::exception("Couldn't initialize GLEW!");
    }

	setup_builtin_shaders();

	_camera = make_owner<Camera>();
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
    for (auto it = _batches.begin(); it != _batches.end(); ++it)
        it->second->render();	

    _mainWindow->swap_buffers();

    // 4# Update GUI
    glfwPollEvents();
}

void RenderEngine::on_shutdown()
{
	// Release OPEN GL Resources
    // Clear Shaders
    _shaders.clear();
    _textures.clear();
    _materials.clear();
    _batches.clear();

    _batchTokenLookup.clear();

	glfwTerminate();
}

void RenderEngine::set_interpolation(float interpol)
{
    // TODO Implement
}

weak<GLWindow> RenderEngine::get_window()
{
    return _mainWindow.get_non_owner();
}

bool RenderEngine::is_exit_requested()
{
    return  _mainWindow->close_requested();
}

// VERTICES
void RenderEngine::remove_vertices(owner<VertexToken> token)
{
	weak<IBatch> batch = _batchTokenLookup[token.get_non_owner()];

	if (batch != nullptr) {
		batch->remove_vertices(std::move( token ));
	}
}

void RenderEngine::add_render(weak<VertexToken> token)
{
    Guard( token.ptr_is_valid() ) return;

    weak<IBatch> batch = _batchTokenLookup[token];

	if (batch != nullptr) {
		batch->add_render(token);
	}
}

void RenderEngine::remove_render(weak<VertexToken> token)
{
    Guard(token.ptr_is_valid()) return;

    weak<IBatch> batch = _batchTokenLookup[token];

	if (batch != nullptr) {
		batch->remove_render(token);
	}
}

// TEXTURE
owner<Texture> RenderEngine::load_texture(string filename, TextureOptions options)
{
    owner<Image> image;
    
    if (StringUtils::ends_with(filename, ".png"))
        image = ImageUtils::load_png(filename);
    else
        LOGGER.log(Level::ERROR) << "Unsupported filetype: " << filename << endl;
    
    return make_owner<Texture>(image.get(), options);
}

weak<Texture> RenderEngine::add_texture(string name, owner<Texture> texture)
{
    _textures.emplace(name, std::move(texture) );
    return _textures[name].get_non_owner();
}

weak<Texture> RenderEngine::get_texture(string name)
{
    if (_textures.count(name) == 1) {
        return _textures[name].get_non_owner();
    }

    return nullptr;
}

bool RenderEngine::has_texture(string name) {
    return _textures.count(name) == 1;
}

// SHADER
weak<Shader> RenderEngine::add_shader(string name, owner<Shader> shader)
{
    _shaders.emplace(name, std::move(shader));
    return _shaders[name].get_non_owner();
}

weak<Shader> RenderEngine::get_shader(string name)
{
    if (_shaders.count(name) == 1) {
        return _shaders[name].get_non_owner();
    }

	return nullptr;
}

bool RenderEngine::has_shader(string name) {
    return _shaders.count(name) == 1;
}

// MATERIAL
weak<Material> RenderEngine::add_material(string name, owner<Material> material)
{
    _materials.emplace(name, std::move(material));
    return _materials[name].get_non_owner();
}

weak<Material> RenderEngine::get_material(string name)
{
    if (_materials.count(name) == 1) {
        return _materials[name].get_non_owner();
    }

    return nullptr;
}

bool RenderEngine::has_material(string name) {
    return _materials.count(name) == 1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void RenderEngine::init_context_and_window()
{
    _mainWindow = make_owner<GLWindow>("Test", 800, 600);
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

	owner<Shader> colorShader = ShaderBuilder()
		.vertex_uniform("mat4", "uni_wvp")
		.vertexlayout(pcLayout)
		.vertex_source(csVertexShader.str())
		.frag_source(csFragmentShader.str())
		.build();

	add_shader("builtin_diffuse", std::move( colorShader ));

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

	owner<Shader> texShader = ShaderBuilder()
		.vertex_uniform("mat4", "uni_wvp")
		.frag_texture_slot(TextureSlotTemplate::TEXTURE_DIFFUSE)
		.vertexlayout(ptLayout)
		.vertex_source(tsVertexShader.str())
		.frag_source(tsFragmentShader.str())
		.build();

	add_shader("builtin_texture", std::move( texShader ));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger RenderEngine::LOGGER = Logger("RenderEngine", Level::DEBUG);

ENGINE_NAMESPACE_END
