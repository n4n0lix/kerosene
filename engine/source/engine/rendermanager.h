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

    s_ptr<Texture>      load_texture(string filename, TextureOptions options = TextureOptions());
    s_ptr<Texture>      overwrite_texture(string filename, s_ptr<Texture> texture);

    s_ptr<Shader>       load_shader(string filename);
    s_ptr<Shader>       overwrite_shader(string filename, s_ptr<Shader> shader);

    s_ptr<Material>     load_material(s_ptr<Shader> shader, s_ptr<Texture> texture);

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

    Map< string, s_ptr<Texture>>                                _texturesByFile;
    Map< string, s_ptr<Shader>>                                 _shadersByFile;
    Map< pair<s_ptr<Shader>,s_ptr<Texture>>, s_ptr<Material>>   _materials;

    Map<s_ptr<Material>, s_ptr<IBatch>>     _materialToBatches;
    Map<s_ptr<VertexToken>, s_ptr<IBatch>>  _tokenToBatches;
};

template<class VERTEX>
inline s_ptr<VertexToken> RenderManager::add_vertices(s_ptr<Material> material, Vector<VERTEX> vertices)
{
    s_ptr<Batch<VERTEX>> batch = dynamic_pointer_cast<Batch<VERTEX>>( _materialToBatches.get( material ) );

    if (batch == nullptr) {
        batch = make_shared<Batch<VERTEX>>( material );
        _materialToBatches.put( material, batch );
    }

    s_ptr<VertexToken> token = batch->add_vertices(vertices);
    _tokenToBatches.put( token, batch );
    return token;
}


ENGINE_NAMESPACE_END
