// Header
#include "inputengine.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

InputEngine::InputEngine()
{

}

void InputEngine::on_start()
{

}

void InputEngine::on_update()
{
    // 1# Store events
    // 1.1# Key events
    _keyGLFWQueueMutex.lock(); 
    {
        _keyQueue = queue<KeyEvent>();
        _keyQueue.swap( _keyGLFWQueue );
    } 
    _keyGLFWQueueMutex.unlock();

    // 1.2# Char events
    _charGLFWQueueMutex.lock();
    {
        _charQueue = queue<CharEvent>();
        _charQueue.swap( _charGLFWQueue );
    }
    _charGLFWQueueMutex.unlock();
    
    // 1.3# Mouse events
    _mouseGLFWQueueMutex.lock();
    {
        _mouseQueue = queue<MouseEvent>();
        _mouseQueue.swap( _mouseGLFWQueue );
    }
    _mouseGLFWQueueMutex.unlock();
}

void InputEngine::on_shutdown()
{

}

void InputEngine::add_keyevent( KeyEvent key )
{
    _keyGLFWQueueMutex.lock();
    _keyGLFWQueue.push( key );
    _keyGLFWQueueMutex.unlock();
}

void InputEngine::add_charevent( CharEvent chr )
{
    _charGLFWQueueMutex.lock();
    _charGLFWQueue.push( chr );
    _charGLFWQueueMutex.unlock();
}

void InputEngine::add_mouseevent( MouseEvent mouseEvent )
{
    _mouseGLFWQueueMutex.lock();
    _mouseGLFWQueue.push( mouseEvent );
    _mouseGLFWQueueMutex.unlock();
}

void InputEngine::set_mouse_position( double mx, double my )
{
    _mx = mx;
    _my = my;
}

queue<KeyEvent> InputEngine::get_keyevents()
{
    return _keyQueue;
}

queue<CharEvent> InputEngine::get_charevents()
{
    return _charQueue;
}

queue<MouseEvent> InputEngine::get_mouseevents()
{
    return _mouseQueue;
}

double InputEngine::get_mouse_x()
{
    return _mx;
}

double InputEngine::get_mouse_y()
{
    return _my;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
