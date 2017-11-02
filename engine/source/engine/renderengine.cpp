#include "stdafx.h"
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

    // 2# Setup callbacks
    if ( input.is_ptr_valid() && input != nullptr ) {
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
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    for ( auto& scene : _scenes ) {
        scene->render( *this, extrapolation );
    }

    _mainWindow->swap_buffers();

    // 4# Update GUI
    glfwPollEvents();
}

void RenderEngine::on_shutdown()
{
    unload_everything();
    destroy_context_and_window();
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
        LOGGER.log(Level::ERROR) << "Unsupported filetype: " << filename << "\n";
    
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

owner<Scene> RenderEngine::remove_scene( weak<Scene> scene )
{
    return extract_owner( _scenes, scene );
}

void RenderEngine::unload_everything()
{
    _shaders.clear();
    _textures.clear();

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
    _mainWindow->make_current();
    std::cout << "Using OpenGL Version " << glGetString(GL_VERSION) << "\n";

    // Enable transparency
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_ALPHA_TEST );
    glAlphaFunc( GL_GREATER, 0 );

    // Depth
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
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
                  /* VertexLayout  */   Vertex_pc().layout,
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
//#ifdef MAT4_ROW_MAJOR
//		<< "    gl_Position = " << Uniform::WORLD_VIEW_PROJ_MATRIX.gl_varname() << " * vec4(position, 1.0);\n"
//#else
        << "    gl_Position = vec4(position, 1.0) * " << Uniform::WORLD_VIEW_PROJ_MATRIX.gl_varname() << ";\n"
//#endif
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
        /* VertexLayout  */   Vertex_pt().layout,
        /* VertexUniform */   { Uniform::WORLD_VIEW_PROJ_MATRIX },
        /* FragUniform   */   {},
        /* Texture Slots */   { TextureSlot::TEXTURE_DIFFUSE },
        /* Vertex Shader */   tsVertexShader.str(),
        /* Frag Shader   */   tsFragmentShader.str()
    ) );

	add_shader("builtin_texture", std::move( texShader ));
}

void RenderEngine::destroy_context_and_window()
{
    _mainWindow.destroy();
    glfwTerminate();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger RenderEngine::LOGGER = Logger("RenderEngine", Level::DEBUG);

ENGINE_NAMESPACE_END
