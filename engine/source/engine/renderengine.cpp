// Header
#include "renderengine.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void RenderEngine::on_start( weak<InputEngine> input )
{
    // 1# Setup glfw
    if (!glfwInit()) {
        throw std::exception("Couldn't initialize GLFW!");
    }

    init_context_and_window();

    if (glewInit() != GLEW_OK) {
        throw std::exception("Couldn't initialize GLEW!");
    }

	setup_builtin_shaders();

	_camera = make_owner<Camera2D>();

    // 2# Setup callbacks
    if ( input.ptr_is_valid() && input != nullptr ) {
        glfwSetWindowUserPointer( _mainWindow->get_handle(), input.get() );

        // 2.1# Key callback
        auto keyCallback = []( GLFWwindow* window, int key, int scancode, int action, int mods )
        {
            static_cast<InputEngine*>(glfwGetWindowUserPointer( window ))->add_keyevent( KeyEvent(key, scancode, action, mods) );
        };
        glfwSetKeyCallback( _mainWindow->get_handle(), keyCallback );

        // 2.2# Char callback
        auto charCallback = []( GLFWwindow* window, unsigned int codepoint, int mods )
        {
            static_cast<InputEngine*>(glfwGetWindowUserPointer( window ))->add_charevent( CharEvent( codepoint, mods ));
        };
        glfwSetCharModsCallback( _mainWindow->get_handle(), charCallback );

        // 2.3# Mouse pos callback
        auto mPosCallback = []( GLFWwindow* window, double xpos, double ypos )
        {
            static_cast<InputEngine*>(glfwGetWindowUserPointer( window ))->add_mouseevent( MoveEvent( xpos, ypos ) );
        };
        glfwSetCursorPosCallback( _mainWindow->get_handle(), mPosCallback );

        // 2.4# Mouse enter/leave
        auto mEnterLeaveCallback = []( GLFWwindow* window, int entered )
        {
            if (entered)
                static_cast<InputEngine*>(glfwGetWindowUserPointer( window ))->add_mouseevent( EnterEvent() );
            else
                static_cast<InputEngine*>(glfwGetWindowUserPointer( window ))->add_mouseevent( LeaveEvent() );
        };
        glfwSetCursorEnterCallback( _mainWindow->get_handle(), mEnterLeaveCallback );

        // 2.4# Mouse button
        auto mClickCallback = [](GLFWwindow* window, int button, int action, int mods)
        {
            double x, y;
            glfwGetCursorPos( window, &x, &y );

            static_cast<InputEngine*>(glfwGetWindowUserPointer( window ))->add_mouseevent( ClickEvent(x,y,button,action,mods) );
        };
        glfwSetMouseButtonCallback( _mainWindow->get_handle(), mClickCallback );

        // 2.5# Scroll input
        auto mScrollCallback = []( GLFWwindow* window, double xoffset, double yoffset )
        { 
            static_cast<InputEngine*>(glfwGetWindowUserPointer( window ))->add_mouseevent( ScrollEvent( xoffset, yoffset ) ); 
        };
        glfwSetScrollCallback( _mainWindow->get_handle(), mScrollCallback );
    }
    
}

void RenderEngine::on_render( float extrapolation )
{
	// 1# Setup rendering
    _mainWindow->make_current();

    // TODO: Sort scenes
    for ( auto it = _scenes.begin(); it != _scenes.end(); ++it ) {
        it->get()->render( *this, extrapolation );
    }

    _mainWindow->swap_buffers();

    // 4# Update GUI
    glfwPollEvents();
}

void RenderEngine::on_shutdown()
{
	// Release OPEN GL Resources
    unload_everything();

    _mainWindow.destroy();

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

void RenderEngine::hide_cursor( bool hideCursor )
{
    glfwSetInputMode( _mainWindow->get_handle(), GLFW_CURSOR, hideCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL );
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

weak<Texture> RenderEngine::add_texture(string filename, owner<Texture> texture)
{
    _textures.emplace( filename, std::move(texture) );
    return _textures[filename].get_non_owner();
}

weak<Texture> RenderEngine::get_texture(string filename )
{
    if (_textures.count( filename ) == 1) {
        return _textures[filename].get_non_owner();
    }

    owner<Texture> oTex = load_texture( filename );
    weak<Texture>  wTex = oTex.get_non_owner();

    if ( oTex != nullptr ) {
        _textures.emplace( filename, std::move( oTex ) );
    }

    return wTex;
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

weak<Scene> RenderEngine::add_scene( owner<Scene> scene )
{
    weak<Scene> weak = scene.get_non_owner();
    _scenes.emplace_back( std::move( scene ));
    return weak;
}

owner<Scene>&& RenderEngine::remove_scene( weak<Scene> scene )
{
    return extract_owner( _scenes, scene );
}

void RenderEngine::unload_everything()
{
    _shaders.clear();
    _textures.clear();
    _materials.clear();

    // TODO: Duplicate code with unload_everything()
    for ( auto it = _scenes.begin(); it != _scenes.end(); ++it ) {
        it->get()->cleanup( *this );
    }
    _scenes.clear();
}

void RenderEngine::on_gamestate_end()
{
    // TODO: Duplicate code with unload_everything()
    for ( auto it = _scenes.begin(); it != _scenes.end(); ++it ) {
        it->get()->cleanup( *this );
    }
    _scenes.clear();
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
	// SETUP BUILT-IN SHADER
	// COLOR SHADER
	///////////
	std::ostringstream csVertexShader;
	csVertexShader
		<< "out vec4 fs_color;\n"
		<< "\n"
		<< "void main() {\n"
		<< "    gl_Position = vec4(position, 1.0);\n"
		<< "    fs_color = color;\n"
		<< "}\n";

    std::ostringstream csFragmentShader;
	csFragmentShader
		<< "in vec4 fs_color;\n"
		<< "\n"
		<< "out vec4 out_color;\n"
		<< "\n"
		<< "void main() {\n"
		<< "    out_color = fs_color;\n"
		<< "}\n";

    owner<Shader> colorShader = owner<Shader>(new Shader( 
                  /* VertexLayout  */   Vertex_pc().layout(),
                  /* VertexUniform */   { Uniform::WORLD_VIEW_PROJ_MATRIX }, 
                  /* FragUniform   */   {}, 
                  /* Texture Slots */   {}, 
                  /* Vertex Shader */   csVertexShader.str(), 
                  /* Frag Shader   */   csFragmentShader.str()
                                ));


	add_shader("builtin_diffuse", std::move( colorShader ));

	// TEXTURE SHADER
	///////////
    std::ostringstream tsVertexShader;
	tsVertexShader
		<< "out vec2 fs_texcoords;\n"
		<< "\n"
		<< "void main() {\n"
		<< "    gl_Position = vec4(position, 1.0) * " << Uniform::WORLD_VIEW_PROJ_MATRIX.gl_varname() << ";\n"
		<< "    fs_texcoords = texcoords;\n"
		<< "}\n";

    std::ostringstream tsFragmentShader;
	tsFragmentShader
		<< "in vec2 fs_texcoords;\n"
		<< "\n"
		<< "out vec4 out_color;\n"
		<< "\n"
		<< "void main() {\n"
		<< "    out_color = texture(" << TextureSlot::TEXTURE_DIFFUSE.name << ", fs_texcoords);\n"
		<< "}\n";

    owner<Shader> texShader = owner<Shader>( new Shader(
        /* VertexLayout  */   Vertex_pt().layout(),
        /* VertexUniform */   { Uniform::WORLD_VIEW_PROJ_MATRIX },
        /* FragUniform   */   {},
        /* Texture Slots */   { TextureSlot::TEXTURE_DIFFUSE },
        /* Vertex Shader */   tsVertexShader.str(),
        /* Frag Shader   */   tsFragmentShader.str()
    ) );

	add_shader("builtin_texture", std::move( texShader ));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger RenderEngine::LOGGER = Logger("RenderEngine", Level::DEBUG);

ENGINE_NAMESPACE_END
