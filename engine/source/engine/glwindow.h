#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes
#include "glfw3.h"

// Internal Includes
#include "_global.h"
#include "engineexception.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

struct GLFWwindowDestroyer {

    void operator()(GLFWwindow* ptr) {
        glfwDestroyWindow(ptr);
    }

};

class GLWindow
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit GLWindow(const string title="Kerosine Engine", const int32_t width=800, const int32_t height=600);
            ~GLWindow();


     void    show();
     void    hide();

     void    set_title(string title);
     string  get_title();

     void    set_width(int32_t width);
     int32   get_width();

     void    set_height(int32_t height);
     int32   get_height();

     void    set_x(int32_t x);
     int32   get_x();

     void    set_y(int32_t y);
     int32   get_y();

     int32   get_renderwidth();
     int32   get_renderheight();

     bool    close_requested();

     inline void    swap_buffers()
     {
         glfwSwapBuffers(_handle.get());
     }

     inline void    make_current()
     {
         if (GLWindow::CURRENT_CONTEXT != _handle.get()) {
             glfwMakeContextCurrent(_handle.get());
             GLWindow::CURRENT_CONTEXT = _handle.get();
         }
     }

     inline void    unmake_current()
     {
         if (GLWindow::CURRENT_CONTEXT == _handle.get()) {
             glfwMakeContextCurrent(nullptr);
             GLWindow::CURRENT_CONTEXT = nullptr;
         }
     }


private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    unique_ptr<GLFWwindow, GLFWwindowDestroyer> _handle;
    
    string _title;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static GLFWwindow* CURRENT_CONTEXT;
};

ENGINE_NAMESPACE_END
