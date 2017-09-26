#include "scene.h"

ENGINE_NAMESPACE_BEGIN

weak<Camera> Scene::add_camera( owner<Camera> cam )
{
    weak<Camera> weak = cam.get_non_owner();
    _cameras.emplace_back( std::move( cam ) );
    return weak;
}

owner<Camera>&& Scene::remove_camera( weak<Camera> cam )
{
    return extract_owner( _cameras, cam );
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

owner<Renderer>&& Scene::remove_renderer( weak<Renderer> renderer )
{
    if ( contains_owner( _ownerRenderers, renderer ) ) {
        _renderers.erase( std::remove( _renderers.begin(), _renderers.end(), renderer ) );
        _uninitRenderers.erase( std::remove( _uninitRenderers.begin(), _uninitRenderers.end(), renderer ) );
        return extract_owner( _ownerRenderers, renderer );
    }

    return std::move(owner<Renderer>(nullptr));
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
    for ( auto it = _cameras.begin(); it != _cameras.end(); ++it) {
        auto camera = it->get_non_owner();
        camera->set_as_active();
        Matrix4f projViewMatrix = camera->proj_view_matrix();

        for ( weak<Renderer> renderer : _renderers ) {
            renderer->render( camera, projViewMatrix );
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

