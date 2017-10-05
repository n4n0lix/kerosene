#pragma once

// Std-Includes

// Other Includes
#include "glfw3.h"

// Internal Includes
#include "_global.h"


ENGINE_NAMESPACE_BEGIN

struct GLFWwindowDestroyer {

    void operator()( GLFWwindow* ptr ) {
        glfwDestroyWindow( ptr );
    }

};

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

    inline void    swap_buffers()
    {
        glfwSwapBuffers( _handle );
    }

    inline void    make_current()
    {
        if ( GLWindow::CURRENT_CONTEXT != _handle ) {
            glfwMakeContextCurrent( _handle );
            GLWindow::CURRENT_CONTEXT = _handle;
        }
    }

    inline void    unmake_current()
    {
        if ( GLWindow::CURRENT_CONTEXT == _handle ) {
            glfwMakeContextCurrent( nullptr );
            GLWindow::CURRENT_CONTEXT = nullptr;
        }
    }


private:
            GLFWwindow* _handle;
            string      _title;


    static  GLFWwindow* CURRENT_CONTEXT;
};

ENGINE_NAMESPACE_END
