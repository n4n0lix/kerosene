// Header
#include "shader.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Public Static                      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Uniform
ShaderUniform Shader::Uni_WVP                  = { "mat4", "uni_wvp" };

// General                                         Type     Name                   Location  Size
ShaderLocation Shader::VAttr_Position          = { "vec3", "vs_pos",               0 };
ShaderLocation Shader::VAttr_Color             = { "vec4", "vs_color",             1 };
ShaderLocation Shader::VAttr_InstancePosition  = { "mat4", "vs_instance_position", 6 };

// Texture 1
ShaderLocation Shader::VAttr_Tex1Coords        = { "vec2", "vs_tex1_coords",       10 };

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool Shader::operator==(const Shader & o) const
{
    return _id == o._id;
}

bool Shader::operator!=(const Shader & o) const
{
    return !(*this == o);
}

bool Shader::operator<(const Shader & o1) const
{
    return _id < o1._id;
}

void Shader::bind() const
{
    if (CURRENT_SHADER != _id) {
        glUseProgram(_id);
        CURRENT_SHADER = _id;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Shader::Shader()
{

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GLuint Shader::CURRENT_SHADER = 0;

ENGINE_NAMESPACE_END
