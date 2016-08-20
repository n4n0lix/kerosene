// Header
#include "shader.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Public Static                      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Shader::bind(GLuint shaderId)
{
    if (CURRENT_SHADER != shaderId) {
        glUseProgram(shaderId);
        CURRENT_SHADER = shaderId;
    }
}

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
    Shader::bind(_id);
}

Nullable<Uniform> Shader::vertex_uniform(string name) const
{
    for (auto uniform : _vertexUniforms) {
        if (uniform.name == name) {
            return Nullable<Uniform>( uniform );
        }
    }

    return Nullable<Uniform>();
}

Nullable<Uniform> Shader::frag_uniform(string name) const
{
    for (auto uniform : _fragUniforms) {
        if (uniform.name == name) {
            return Nullable<Uniform>(uniform);
        }
    }

    return Nullable<Uniform>();
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
