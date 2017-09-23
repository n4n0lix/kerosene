// Header
#include "material.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Material::Material(weak<Shader> shader, weak<Texture> tex)
{
    _shader = shader;
    _textureDiffuse = tex;
}

weak<Shader> Material::get_shader() const
{
    return _shader;
}

weak<Texture> Material::get_texture() const
{
    return _textureDiffuse;
}

void Material::bind() const {
    if (_shader.ptr_is_valid() && _shader != nullptr) {
        _shader->bind();
        if (_textureDiffuse != nullptr) {
            // TEXTURE_DIFFUSE
            TextureSlot slot0 = _shader->frag_texture_slot(TextureSlot::TEXTURE_DIFFUSE.name).get();
            glUniform1i(slot0.location, slot0.slot);
            glActiveTexture(slot0.glTextureSlot);
            glBindTexture(GL_TEXTURE_2D, _textureDiffuse->id());
        }
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END

