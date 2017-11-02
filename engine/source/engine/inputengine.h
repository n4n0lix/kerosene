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

#include "localcontroller.h"

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

    void add_local_controller( uint32 priority, owner<LocalController> );

    // INPUT
    void add_keyevent( KeyEvent keyEvent );
    void add_charevent( CharEvent charEvent );
    void add_mouseevent( MouseEvent mouseEvent );

    void set_mouse_position( double mx, double my );

    // OUTPUT
    std::vector<KeyEvent>&    get_keyevents();
    std::vector<CharEvent>&   get_charevents();
    std::vector<MouseEvent>&  get_mouseevents();

    double get_mouse_x();
    double get_mouse_y();

private:
    map<uint32, owner<LocalController>> _localControllers;

    std::vector<KeyEvent>   _keyQueue;
    std::vector<KeyEvent>   _keyGLFWQueue;
    std::mutex              _keyGLFWQueueMutex;

    std::vector<CharEvent>  _charQueue;
    std::vector<CharEvent>  _charGLFWQueue;
    std::mutex              _charGLFWQueueMutex;

    std::vector<MouseEvent> _mouseQueue;
    std::vector<MouseEvent> _mouseGLFWQueue;
    std::mutex              _mouseGLFWQueueMutex;

    double                  _mx;
    double                  _my;
};

ENGINE_NAMESPACE_END

