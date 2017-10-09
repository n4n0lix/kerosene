#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "glfw3.h"

ENGINE_NAMESPACE_BEGIN

class KeyEvent
{
public:
            KeyEvent( int32 key, int32 scancode, int32 action, int32 mods )
                : _key( key ), _scancode( scancode ), _action( action ), _mods( mods ) { }

    inline int32 key()      { return _key; }
    inline int32 scancode() { return _scancode; }
    inline int32 action()   { return _action; }

    inline bool shift() { return _mods & GLFW_MOD_SHIFT; }
    inline bool ctrl()  { return _mods & GLFW_MOD_CONTROL; }
    inline bool alt()   { return _mods & GLFW_MOD_ALT; }
    inline bool super() { return _mods & GLFW_MOD_SUPER; }

    inline bool pressed() { return _action == GLFW_PRESS; }
    inline bool released() { return _action == GLFW_RELEASE; }

private:

    int32  _key;
    int32  _scancode;
    int32  _action;
    int32  _mods;
};


enum Key {
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,
    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,
    ESCAPE = GLFW_KEY_ESCAPE
};

ENGINE_NAMESPACE_END