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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class CharEvent {
public:
    CharEvent( char32 chr, int32 mods ) : _char( chr ) { }


    inline char32 chr() { return _char; }


    inline bool shift() { return _mods & GLFW_MOD_SHIFT; }
    inline bool ctrl() { return _mods & GLFW_MOD_CONTROL; }
    inline bool alt() { return _mods & GLFW_MOD_ALT; }
    inline bool super() { return _mods & GLFW_MOD_SUPER; }

private:
    char32 _char;
    int32  _mods;
};

class KeyEvent {
public:
    KeyEvent( int32 key, int32 scancode, int32 action, int32 mods )
        : _key( key ), _scancode( scancode ), _action( action ), _mods( mods ) { }

    inline int32 key() { return _key; }
    inline int32 scancode() { return _scancode; }
    inline int32 action() { return _action; }


    inline bool shift() { return _mods & GLFW_MOD_SHIFT; }
    inline bool ctrl() { return _mods & GLFW_MOD_CONTROL; }
    inline bool alt() { return _mods & GLFW_MOD_ALT; }
    inline bool super() { return _mods & GLFW_MOD_SUPER; }

private:
    int32  _key;
    int32  _scancode;
    int32  _action;
    int32  _mods;
};

class MouseEvent {};

class MoveEvent : public MouseEvent {
public:
    MoveEvent( double x, double y ) : _x(x), _y(y) {}

    double x() { return _x; }
    double y() { return _y; }

private:
    double _x;
    double _y;
};

class ClickEvent : public MouseEvent {
public:
            ClickEvent( double x, double y, int button, int action, int mods ) 
                : _x( x ), _y( y ), _button(button), _action(action), _mods(mods) {}

    double x() { return _x; }
    double y() { return _y; }
    int32  button() { return _button; }
    int32  action() { return _action; }
    int32  mods() { return _mods; }

private:
    double _x;
    double _y;
    int32  _button;
    int32  _action;
    int32  _mods;
};

class LeaveEvent : public MouseEvent {
public:
    LeaveEvent() {}

};

class EnterEvent : public MouseEvent {
public:
    EnterEvent() {}
};

class ScrollEvent : public MouseEvent {
public:
    ScrollEvent( double x, double y ) : _x( x ), _y( y ) {}

    double x_offset() { return _x; }
    double y_offset() { return _y; }

private:
    double _x;
    double _y;
};


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

