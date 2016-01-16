#ifndef SHADER_H
#define SHADER_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <vector>
    using std::vector;

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

struct DLL_PUBLIC ShaderUniform {
    string  type;
    string  name;

    bool operator==(const ShaderUniform& o) { return type == o.type && name == o.name; }
    bool operator!=(const ShaderUniform& o) { return !(*this == o); }
};

struct DLL_PUBLIC ShaderLocation {
    string  type;
    string  name;
    int32_t position;

    bool operator==(const ShaderLocation& o) { return type == o.type && name == o.name && position == o.position; }
    bool operator!=(const ShaderLocation& o) { return !(*this == o); }
};

class DLL_PUBLIC Shader
{
    friend class ShaderBuilder;
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // Uniform
    static ShaderUniform  Uni_WVP;

    // General
    static ShaderLocation VAttr_Position;
    static ShaderLocation VAttr_Color;
    static ShaderLocation VAttr_InstancePosition;

    // Texture 1
    static ShaderLocation VAttr_Tex1Coords;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    bool operator==(const Shader& o) const;
    bool operator!=(const Shader& o) const;

    // TODO: Find a better way, this doesn't say that this shader is "smaller"
    bool operator<(const Shader& o1) const; // To be able to use in map

    void bind() const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Shader();

    GLuint  _id;

    vector<ShaderUniform>  _uniforms;
    vector<ShaderLocation> _locations;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static GLuint CURRENT_SHADER;
};
ENGINE_NAMESPACE_END

#endif // SHADER_H
