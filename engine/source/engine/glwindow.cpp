// Header
#include "glwindow.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLWindow::GLWindow(const string title, const int32_t width, const int32_t height)
{
    // Configure the window
    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create the window
    _handle = unique_ptr<GLFWwindow, GLFWwindowDestroyer>(glfwCreateWindow(width, height, "Kerosine Engine", nullptr, nullptr), GLFWwindowDestroyer());

    if (_handle == nullptr) {
        throw std::exception("Failed to create the GLFW window");
    }

    set_title(title);
    show();
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(_handle.get());
}

void GLWindow::show()
{
    glfwShowWindow(_handle.get());
}

void GLWindow::hide()
{
    glfwHideWindow(_handle.get());
}

void GLWindow::set_title(string title)
{
    _title = title;
    glfwSetWindowTitle(_handle.get(), title.c_str());
}

string GLWindow::get_title()
{
    return _title;
}

void GLWindow::set_width(int32_t width)
{
    int32_t height = get_height();
    glfwSetWindowSize(_handle.get(), width, height);
}

int32_t GLWindow::get_width()
{
    int32_t width;
    glfwGetWindowSize(_handle.get(), &width, nullptr);
    return width;
}

void GLWindow::set_height(int32_t height)
{
    int32_t width = get_width();
    glfwSetWindowSize(_handle.get(), width, height);
}

int32_t GLWindow::get_height()
{
    int32_t height;
    glfwGetWindowSize(_handle.get(), nullptr, &height);
    return height;
}

void GLWindow::set_x(int32_t x) {
    int32_t y = get_y();
    glfwSetWindowPos(_handle.get(), x, y);
}

int32_t GLWindow::get_x() {
    int32_t x;
    glfwGetWindowPos(_handle.get(), &x, nullptr);
    return x;
}

void GLWindow::set_y(int32_t y) {
    int32_t x = get_x();
    glfwSetWindowPos(_handle.get(), x, y);
}

int32_t GLWindow::get_y() {
    int32_t y;
    glfwGetWindowPos(_handle.get(), nullptr, &y);
    return y;
}

int32_t GLWindow::get_renderwidth()
{
    int width, height;
    glfwGetFramebufferSize(_handle.get(), &width, &height);
    return width;
}

int32_t GLWindow::get_renderheight()
{
    int width, height;
    glfwGetFramebufferSize(_handle.get(), &width, &height);
    return height;
}

bool GLWindow::close_requested()
{
    return glfwWindowShouldClose(_handle.get()) == GL_TRUE;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLFWwindow* GLWindow::CURRENT_CONTEXT = nullptr;

ENGINE_NAMESPACE_END
