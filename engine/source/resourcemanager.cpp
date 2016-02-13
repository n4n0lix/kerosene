// Header
#include "resourcemanager.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Public Static                      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ResourceManager::ResourceManager()
{

}

shared_ptr<Material> ResourceManager::getMaterial(const shared_ptr<Shader> shader, const shared_ptr<Texture> tex)
{
    // 1# Create a key to access the map
    pair<Shader, Texture> materialId = make_pair(*shader, *tex);

    // 2# Get value by key or create new material
    auto iterator = _materials.find(materialId);

    if (iterator == _materials.end()) {
        // 2.1# Get material
        return iterator->second;
    }
    else {
        garbageCollectMaterials();
        // 2.2# Create new material
        shared_ptr<Material> material( new Material(shader, tex) );
        _materials.insert( make_pair(materialId, material) );
        return material;
    }
}

void ResourceManager::garbageCollectMaterials()
{
    cout << "ResourceManager: Start garbage collecting (" << _materials.size() << " active materials)" << std::endl;

    for (auto it = _materials.begin(); it != _materials.end(); it++)
    {
        // If the manager has the unique owning pointer, garbage collect it
        if (it->second.unique()) {
            pair<Shader, Texture> key   = it->first;
            shared_ptr<Material>  value = it->second;
            _materials.erase(key);
        }
    }

    cout << "ResourceManager: Finished garbage collecting (" << _materials.size() << " active materials)" << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
