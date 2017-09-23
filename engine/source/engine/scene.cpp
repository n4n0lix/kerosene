#include "scene.h"

ENGINE_NAMESPACE_BEGIN

void Scene::add_camera( weak<ICamera> cam )
{
    if ( std::find( _cameras.begin(), _cameras.end(), cam ) != _cameras.end() ) {
        return;
    }

    _cameras.push_back( cam );
}

void Scene::remove_camera( weak<ICamera> cam )
{
    _cameras.erase( std::remove( _cameras.begin(), _cameras.end(), cam ));
}

void Scene::add_gameobject( weak<GameObject> gameobject )
{
    if ( std::find( _gameObjects.begin(), _gameObjects.end(), gameobject ) != _gameObjects.end() ) {
        return;
    }

    _gameObjects.push_back( gameobject );
}

void Scene::remove_gameobject( weak<GameObject> gameobject )
{
    _gameObjects.erase( std::remove( _gameObjects.begin(), _gameObjects.end(), gameobject ) );
}

vector<weak<ICamera>>& Scene::get_cameras()
{
    return _cameras;
}

vector<weak<GameObject>>& Scene::get_gameobjects()
{
    return _gameObjects;
}


ENGINE_NAMESPACE_END

