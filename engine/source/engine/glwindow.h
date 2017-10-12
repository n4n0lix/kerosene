#pragma once

// Std-Includes

// Other Includes
#include "glfw3.h"

// Internal Includes
#include "_global.h"
#include "events.h"


ENGINE_NAMESPACE_BEGIN

class GLWindow
{
public:

            explicit GLWindow( const string title = "Kerosine Engine", const int32_t width = 800, const int32_t height = 600 );
            ~GLWindow();

    void        show();
    void        hide();
    void        set_title( string );
    string      get_title();
    void        set_width( int32_t );
    int32       get_width();
    void        set_height( int32_t );
    int32       get_height();
    void        set_x( int32_t );
    int32       get_x();
    void        set_y( int32_t );
    int32       get_y();
    int32       get_renderwidth();
    int32       get_renderheight();
    bool        close_requested();
    GLFWwindow* get_handle();
    void        swap_buffers();
    void        make_current();
    void        unmake_current();

private:
            GLFWwindow* _handle;
            string      _title;


    static  GLFWwindow* CURRENT_CONTEXT;
};

inline void GLWindow::swap_buffers()
{
    glfwSwapBuffers( _handle );
}

inline void GLWindow::make_current() {
    if ( GLWindow::CURRENT_CONTEXT != _handle ) {
        glfwMakeContextCurrent( _handle );
        GLWindow::CURRENT_CONTEXT = _handle;
    }
}

inline void GLWindow::unmake_current() {
    if ( GLWindow::CURRENT_CONTEXT == _handle ) {
        glfwMakeContextCurrent( nullptr );
        GLWindow::CURRENT_CONTEXT = nullptr;
    }
}

ENGINE_NAMESPACE_END
