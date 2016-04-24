// Header
#include "shader.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Public Static                      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Uniform
Uniform Shader::Uni_WVP                  = { "mat4", "uni_wvp" };

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

shared_ptr<VertexLayout> Shader::getVertexLayout() const
{
    return _vertexLayout;
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
Logger Shader::LOGGER = Logger("Shader", Level::OFF);

ENGINE_NAMESPACE_END
