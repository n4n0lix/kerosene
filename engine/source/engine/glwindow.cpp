#include "stdafx.h"
#include "glwindow.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLWindow::GLWindow(const string title, const int32 width, const int32 height, DisplayMode mode)
{
    // Configure the window
    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create the window
    _handle = glfwCreateWindow( width, 
                                height, 
                                "Kerosine Engine", 
                                nullptr, 
                                nullptr );

    if (_handle == nullptr) {
        throw std::exception("Failed to create the GLFW window");
    }

    set_title(title);
    show();

    set_displaymode( mode );
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(_handle);
}

void GLWindow::set_displaymode( DisplayMode mode )
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* nativeMode = glfwGetVideoMode( monitor );

    switch ( mode )
    {
    case DisplayMode::WINDOWED:
        glfwSwapInterval( -1 ); // Adaptive VSync
        glfwSetWindowMonitor( _handle, nullptr, _x, _y, _width, _height, nativeMode->refreshRate );
        break;

    case DisplayMode::WINDOWED_FULLSCREEN:
        glfwSwapInterval( -1 ); // Adaptive VSync
        glfwSetWindowMonitor( _handle, nullptr, 0, 0, nativeMode->width, nativeMode->height, nativeMode->refreshRate );

        break;

    case DisplayMode::FULLSCREEN:
        glfwSwapInterval( 0 ); // Disable VSync
        glfwSetWindowMonitor( _handle, monitor, 0, 0, nativeMode->width, nativeMode->height, nativeMode->refreshRate );
        break;
    }
}

void GLWindow::show()
{
    glfwShowWindow(_handle);
}

void GLWindow::hide()
{
    glfwHideWindow(_handle);
}

void GLWindow::set_title(string title)
{
    _title = title;
    glfwSetWindowTitle(_handle, _title.c_str());
}

string GLWindow::get_title()
{
    return _title;
}

void GLWindow::set_size( uint32 width, uint32 height)
{
    _width = width;
    _height = height;
    glfwSetWindowSize(_handle, (int32)_width, (int32)_height);
}

uint32 GLWindow::get_width()
{
    return _width;
}

uint32 GLWindow::get_height()
{
    return _height;
}

int32 GLWindow::get_x() {
    return _x;
}

int32 GLWindow::get_y() {
    return _y;
}

void GLWindow::set_pos(int32 x, int32 y) {
    _x = x;
    _y = y;
    glfwSetWindowPos(_handle, _x, _y);
}


int32_t GLWindow::get_renderwidth()
{
    int width, height;
    glfwGetFramebufferSize(_handle, &width, &height);
    return width;
}

int32_t GLWindow::get_renderheight()
{
    int width, height;
    glfwGetFramebufferSize(_handle, &width, &height);
    return height;
}

bool GLWindow::close_requested()
{
    return glfwWindowShouldClose(_handle) == GL_TRUE;
}

GLFWwindow* GLWindow::get_handle() {
    return _handle;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLFWwindow* GLWindow::CURRENT_CONTEXT = nullptr;

ENGINE_NAMESPACE_END
