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
        throw EngineException("Failed to create the GLFW window");
    }

    setTitle(title);
    show();
}

void GLWindow::show()
{
    glfwShowWindow(_handle.get());
}

void GLWindow::hide()
{
    glfwHideWindow(_handle.get());
}

void GLWindow::setTitle(string title)
{
    _title = title;
    glfwSetWindowTitle(_handle.get(), title.c_str());
}

string GLWindow::getTitle()
{
    return _title;
}

void GLWindow::setWidth(int32_t width)
{
    int32_t height = getHeight();
    glfwSetWindowSize(_handle.get(), width, height);
}

int32_t GLWindow::getWidth()
{
    int32_t width;
    glfwGetWindowSize(_handle.get(), &width, nullptr);
    return width;
}

void GLWindow::setHeight(int32_t height)
{
    int32_t width = getWidth();
    glfwSetWindowSize(_handle.get(), width, height);
}

int32_t GLWindow::getHeight()
{
    int32_t height;
    glfwGetWindowSize(_handle.get(), nullptr, &height);
    return height;
}

void GLWindow::setX(int32_t x) {
    int32_t y = getY();
    glfwSetWindowPos(_handle.get(), x, y);
}

int32_t GLWindow::getX() {
    int32_t x;
    glfwGetWindowPos(_handle.get(), &x, nullptr);
    return x;
}

void GLWindow::setY(int32_t y) {
    int32_t x = getX();
    glfwSetWindowPos(_handle.get(), x, y);
}

int32_t GLWindow::getY() {
    int32_t y;
    glfwGetWindowPos(_handle.get(), nullptr, &y);
    return y;
}

int32_t GLWindow::getRenderWidth()
{
    int width, height;
    glfwGetFramebufferSize(_handle.get(), &width, &height);
    return width;
}

int32_t GLWindow::getRenderHeight()
{
    int width, height;
    glfwGetFramebufferSize(_handle.get(), &width, &height);
    return height;
}

bool GLWindow::closeRequested()
{
    return glfwWindowShouldClose(_handle.get()) == GL_TRUE;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLFWwindow* GLWindow::CURRENT_CONTEXT = nullptr;

ENGINE_NAMESPACE_END
