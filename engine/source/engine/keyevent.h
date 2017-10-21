#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "glfw3.h"

ENGINE_NAMESPACE_BEGIN

enum class Key : int32 {
    Unkown, 
    A, B, C, D, E, F, G, H, I, J, K, L, M, 
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,    
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    Escape
};

class KeyEvent
{
    static Key from_keycode( int32 );

public:
    KeyEvent( int32 keycode, int32 scancode, int32 action, int32 mods );

    inline Key   key()      { return _key; }
    inline int32 scancode() { return _scancode; }
    inline int32 action()   { return _action; }

    inline bool shift() { return _mods & GLFW_MOD_SHIFT; }
    inline bool ctrl()  { return _mods & GLFW_MOD_CONTROL; }
    inline bool alt()   { return _mods & GLFW_MOD_ALT; }
    inline bool super() { return _mods & GLFW_MOD_SUPER; }

    inline bool pressed() { return _action == GLFW_PRESS; }
    inline bool released() { return _action == GLFW_RELEASE; }
    inline bool state_changed() { return pressed() || released(); }

    inline bool is_consumed() { return _consumed; }
    inline bool is_not_consumed() { return !_consumed; }
    inline void consume() { _consumed = true; }

private:

    Key    _key;
    int32  _scancode;
    int32  _action;
    int32  _mods;
    bool   _consumed;
};

ENGINE_NAMESPACE_END