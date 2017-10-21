#include "stdafx.h"
#include "scene.h"

ENGINE_NAMESPACE_BEGIN

owner<Camera> Scene::remove_camera( weak<Camera> cam )
{
    return extract_owner( _cameras, cam );
}

owner<Renderer> Scene::remove_renderer( weak<Renderer> renderer )
{
    if ( contains_owner( _ownerRenderers, renderer ) ) {
        _renderers.erase( std::remove( _renderers.begin(), _renderers.end(), renderer ) );
        _uninitRenderers.erase( std::remove( _uninitRenderers.begin(), _uninitRenderers.end(), renderer ) );
        return extract_owner( _ownerRenderers, renderer );
    }

    return std::move( owner<Renderer>( nullptr ) );
}

void Scene::cleanup( RenderEngine& engine )
{
    for ( weak<Renderer> renderer : _renderers ) {
        renderer->cleanup( engine );
    }
}

void Scene::render( RenderEngine& engine, float delta )
{
    initialize_renderers( engine );

    for ( auto& camera : _cameras ) {
        camera->activate( delta );
        Matrix4f projViewMat4 = camera->proj_view_mat4();

        for ( weak<Renderer> renderer : _renderers ) {
            renderer->render( engine, *camera, projViewMat4, delta );
        }
    }
}

void Scene::initialize_renderers( RenderEngine& engine ) {
    if ( _uninitRenderers.size() > 0 ) {
        for ( weak<Renderer> renderer : _uninitRenderers ) {
            renderer->init( engine );
            _renderers.push_back( renderer );
        }

        _uninitRenderers.clear();
    }
}

ENGINE_NAMESPACE_END

