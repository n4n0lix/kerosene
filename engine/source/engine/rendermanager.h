#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

#include "texture.h"
#include "shader.h"
#include "material.h"
#include "batch.h"

#include "vertex_pc.h"
#include "vertex_pt.h"
#include "shaderbuilder.h"
#include "textureslot.h"

#include "imageutils.h"
#include "stringutils.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class RenderManager
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                explicit RenderManager();

    // Resource Managing
    s_ptr<Texture>      load_texture(string filename, TextureOptions options = TextureOptions());
    s_ptr<Texture>      overwrite_texture(string filename, s_ptr<Texture> texture);

    s_ptr<Shader>       load_shader(string filename);
    s_ptr<Shader>       built_in_shader(string name, s_ptr<Shader> shader);

    s_ptr<Material>     load_material(s_ptr<Shader> shader, s_ptr<Texture> texture);

    // Rendering
    template<class VERTEX>
    s_ptr<VertexToken>  add_vertices(s_ptr<Material> material, Vector<VERTEX> vertices);
    void                remove_vertices(s_ptr<VertexToken> token);

    void                add_render(s_ptr<VertexToken> token);
    void                remove_render(s_ptr<VertexToken> token);

    void                render();
private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    void setup_builtin_shaders();


    Map< string, w_ptr<Texture>>                                _fileToTextures;    // Textures          owned by creator
    
    Map< string, w_ptr<Shader>>                                 _fileToShader;      // Shaders           owned by creators
    Map< string, s_ptr<Shader>>                                 _builtinShaders;    // Built-in Shaders  owned by this

    Map< pair<w_ptr<Shader>,w_ptr<Texture>>, w_ptr<Material>>   _materials;         // Materials         owned by creators

    map< w_ptr<Material>,    s_ptr<IBatch>, std::owner_less<w_ptr<Material>>>      _materialToBatches; // Batches           owned by this
    map< w_ptr<VertexToken>, s_ptr<IBatch>, std::owner_less<w_ptr<VertexToken>>>   _tokenToBatches;    // Batches           owned by this


    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;

};

template<class VERTEX>
inline s_ptr<VertexToken> RenderManager::add_vertices(s_ptr<Material> material, Vector<VERTEX> vertices)
{
    // #1.1 Get batch if already one exists...
    s_ptr<Batch<VERTEX>> batch = dynamic_pointer_cast<Batch<VERTEX>>( _materialToBatches[ material ] );

    // #1.2 ... or create a new one
    if (batch == nullptr) {
        batch = make_shared<Batch<VERTEX>>( material );
        _materialToBatches[ material ] = batch;
    }

    // #2 Add vertices to batch
    s_ptr<VertexToken> token = batch->add_vertices(vertices);
    _tokenToBatches[ token ] = batch;
    return token;
}


ENGINE_NAMESPACE_END
