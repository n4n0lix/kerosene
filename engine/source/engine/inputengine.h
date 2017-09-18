#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <mutex>

// Other Includes

// Internal Includes
#include "_global.h"
#include "glfw3.h"
#include "glwindow.h"

#include "keyevent.h"
#include "charevent.h"
#include "mouseevent.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class InputEngine
{
public:

			InputEngine();
            ~InputEngine() = default;

    void on_start();
    void on_update();
    void on_shutdown();

    // INPUT
    void add_keyevent( KeyEvent keyEvent );
    void add_charevent( CharEvent charEvent );
    void add_mouseevent( MouseEvent mouseEvent );

    void set_mouse_position( double mx, double my );

    // OUTPUT
    queue<KeyEvent>    get_keyevents();
    queue<CharEvent>   get_charevents();
    queue<MouseEvent>  get_mouseevents();

    double get_mouse_x();
    double get_mouse_y();

private:
    queue<KeyEvent>         _keyQueue;
    queue<KeyEvent>         _keyGLFWQueue;
    std::mutex              _keyGLFWQueueMutex;

    queue<CharEvent>        _charQueue;
    queue<CharEvent>        _charGLFWQueue;
    std::mutex              _charGLFWQueueMutex;

    queue<MouseEvent>       _mouseQueue;
    queue<MouseEvent>       _mouseGLFWQueue;
    std::mutex              _mouseGLFWQueueMutex;

    double                  _mx;
    double                  _my;
};

ENGINE_NAMESPACE_END

