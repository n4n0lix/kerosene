#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "noncopyable.h"
#include "camera.h"

#include "renderer.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class Renderer;
class RenderEngine;

class priority_less
{
public:
    bool operator() ( const weak<Renderer>& r0, const weak<Renderer>& r1 );
};

class Scene : public noncopyable
{
public:
    template<typename T>
    weak<T>           add_camera();
    template<typename T>
    weak<T>           add_camera( owner<T> camera );

    owner<Camera>     remove_camera( weak<Camera> );
    
    template<typename T>
    weak<T>           add_renderer();

    template<typename T, typename... Arguments>
    weak<T>           add_renderer( Arguments&&... );

    template<typename T>
    weak<T>           add_renderer( owner<T> renderer );

    owner<Renderer>   remove_renderer( weak<Renderer> );

    void              render( RenderEngine&, float extrapolation );
    void              cleanup( RenderEngine& );

private:
    void    initialize_renderers( RenderEngine& engine );
    void    cleanup_renderers();
    void    sort_renderers();

    std::vector<owner<Camera>>    _cameras;

    std::vector<owner<Renderer>>    _ownerRenderers;
    std::vector<weak<Renderer>>     _uninitRenderers;
    std::vector<weak<Renderer>>     _renderers;

};

template<typename T>
weak<T> Scene::add_camera(owner<T> cam)
{
    static_assert(std::is_base_of<Camera, T>::value, "T must inherit from Camera");

    weak<T> weakCamera = cam.get_non_owner();
    _cameras.emplace_back( std::move( cam ) );
    return weakCamera;
}

template<typename T>
weak<T> Scene::add_camera()
{ 
    static_assert(std::is_base_of<Camera, T>::value, "T must inherit from Camera");
    static_assert(std::is_constructible<T>::value, "T must be default constructible");

    return add_camera<T>( make_owner<T>() );
}

template<typename T>
weak<T> Scene::add_renderer()
{
    static_assert(std::is_base_of<Renderer, T>::value, "T must inherit from Renderer");
    static_assert(std::is_constructible<T>::value, "T must be default constructible");

    return add_renderer( std::move( make_owner<T>() ) );
}

template<typename T, typename ...Arguments>
weak<T> Scene::add_renderer( Arguments&&... args )
{
    auto renderer = make_owner<T>( std::forward<Arguments>( args )... );
    return add_renderer<T>( std::move( renderer ) );
}

template<typename T>
weak<T> Scene::add_renderer( owner<T> renderer ) 
{ 
    static_assert(std::is_base_of<Renderer, T>::value, "T must inherit from Renderer");

    weak<T> weakT = renderer.get_non_owner();
    weak<Renderer> weakR = (weak<Renderer>) weakT;

    _ownerRenderers.emplace_back( std::move( renderer ) );

    if ( !weakR->is_initialized() ) {
        _uninitRenderers.push_back( weakR );
    }
    else {
        _renderers.push_back( weakR );
    }

    return weakT;
}

ENGINE_NAMESPACE_END
