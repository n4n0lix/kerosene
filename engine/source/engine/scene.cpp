#include "scene.h"

ENGINE_NAMESPACE_BEGIN

void Scene::add_camera( weak<Camera> cam )
{
    if ( std::find( _cameras.begin(), _cameras.end(), cam ) != _cameras.end() ) {
        return;
    }

    _cameras.push_back( cam );
}

void Scene::remove_camera( weak<Camera> cam )
{
    _cameras.erase( std::remove( _cameras.begin(), _cameras.end(), cam ));
}

weak<Renderer> Scene::add_renderer( owner<Renderer> renderer )
{
    weak<Renderer> weakRenderer = renderer.get_non_owner();
    _ownerRenderers.emplace_back( std::move( renderer ) );
   
    if ( !weakRenderer->is_initialized() ) {
        _uninitRenderers.push_back( weakRenderer );
    }
    else {
        _renderers.push_back( weakRenderer );
    }

    return weakRenderer;
}

owner<Renderer> Scene::remove_renderer( weak<Renderer> renderer )
{
    if ( contains_owner( _ownerRenderers, renderer ) ) {
        _renderers.erase( std::remove( _renderers.begin(), _renderers.end(), renderer ) );
        _uninitRenderers.erase( std::remove( _uninitRenderers.begin(), _uninitRenderers.end(), renderer ) );
        return std::move( extract_owner( _ownerRenderers, renderer ));
    }

    return nullptr;
}

vector<weak<Camera>>& Scene::get_cameras()
{
    return _cameras;
}

void  Scene::render( weak<RenderEngine> render ) {

    // 1# Initialze renderers if needed
    if ( _uninitRenderers.size() > 0 ) {
        for ( weak<Renderer> renderer : _uninitRenderers ) {
            renderer->init( render );
            _renderers.push_back( renderer );
        }

        _uninitRenderers.clear();
    }

    // 2# Render Scene
    for ( weak<Camera> camera : _cameras ) {

        camera->set_as_active();

        for ( weak<Renderer> renderer : _renderers ) {
            renderer->render();
        }
    }
}

void Scene::cleanup()
{
    for ( weak<Renderer> renderer : _renderers ) {
        renderer->cleanup();
    }
}


ENGINE_NAMESPACE_END

