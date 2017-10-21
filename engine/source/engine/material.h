#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "shader.h"
#include "texture.h"

ENGINE_NAMESPACE_BEGIN

class Material
{
public:
    void            set_shader( weak<Shader> shader );
    weak<Shader>    get_shader() const;

    void            set_texture_diffuse( weak<Texture> texture );
    weak<Texture>   get_texture_diffuse() const;

    HOTPATH void    set_wvp( Matrix4f wvp );
    HOTPATH void    bind() const;

private:
    weak<Shader>  _shader;
    weak<Texture> _textureDiffuse;

};

inline void Material::set_wvp( Matrix4f wvp )
{
    if ( _shader ) {
        _shader->set_vertex_uniform( Uniform::WORLD_VIEW_PROJ_MATRIX, wvp );
    }
}

inline void Material::bind() const {
    if ( _shader ) {
        _shader->bind();

        if ( _textureDiffuse ) {
            TextureSlot slot0 = _shader->frag_texture_slot( TextureSlot::TEXTURE_DIFFUSE.name ).get();
            glUniform1i( slot0.location, slot0.slot );
            glActiveTexture( slot0.glTextureSlot );
            glBindTexture( GL_TEXTURE_2D, _textureDiffuse->id() );
        }
    }
}

ENGINE_NAMESPACE_END
