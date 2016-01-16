#ifndef GLWINDOW_H
#define GLWINDOW_H

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

class DLL_PUBLIC GLWindow
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit GLWindow(string title="Kerosine Engine", int32_t width=800, int32_t height=600);
            ~GLWindow();

     void    show();
     void    hide();

     void    setTitle(string title);
     string  getTitle();

     void    setWidth(int32_t width);
     int32_t getWidth();

     void    setHeight(int32_t height);
     int32_t getHeight();

     int32_t getRenderWidth();
     int32_t getRenderHeight();

     bool    closeRequested();

     inline void    swapBuffers()
     {
         glfwSwapBuffers(_handle);
     }

     inline void    makeCurrent()
     {
         if (GLWindow::CURRENT_CONTEXT != _handle) {
             glfwMakeContextCurrent(_handle);
             GLWindow::CURRENT_CONTEXT = _handle;
         }
     }

     inline void    unmakeCurrent()
     {
         if (GLWindow::CURRENT_CONTEXT == _handle) {
             glfwMakeContextCurrent(nullptr);
             GLWindow::CURRENT_CONTEXT = nullptr;
         }
     }


private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GLFWwindow* _handle;
    
    string _title;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static GLFWwindow* CURRENT_CONTEXT;
};

ENGINE_NAMESPACE_END
#endif // GLWINDOW_H
