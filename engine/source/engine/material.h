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
            Material( weak<Shader> shader, weak<Texture> tex = nullptr );
            ~Material() = default;

    weak<Shader>  get_shader() const;
    weak<Texture> get_texture() const;

    void          bind() const;

private:
    weak<Shader>  _shader;
    weak<Texture> _textureDiffuse;

};

ENGINE_NAMESPACE_END
