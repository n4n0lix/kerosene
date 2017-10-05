#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

ENGINE_NAMESPACE_BEGIN

class CharEvent
{
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

ENGINE_NAMESPACE_END
