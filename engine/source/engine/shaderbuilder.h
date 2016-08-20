#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>
#include <sstream> 
    using std::ostringstream;
#include <algorithm>

// Other Includes

// Internal Includes
#include "_global.h"
#include "_gl.h"

#include "vertex.h"
#include "shader.h"
#include "engineexception.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class ShaderBuilder
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit ShaderBuilder();

    ShaderBuilder& vertexlayout(shared_ptr<VertexLayout> layout);
    ShaderBuilder& vertex_uniform(Uniform uniform);
    ShaderBuilder& frag_uniform(Uniform uniform);

    // TODO: PerInstance Layout

    ShaderBuilder& vertex_source(string vscode);
    ShaderBuilder& frag_source(string fscode);

    unique_ptr<Shader> build() const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   

    string                  gen_vertex_source() const;
    string                  gen_fragment_source() const;
    GLuint                  create_shader(GLenum shaderType) const;
    GLuint                  link_program(GLuint vertexShader, GLuint fragmentShader) const;
    Vector<Uniform>         process_uniforms(GLuint shaderId, const Vector<Uniform>* uniforms) const;

    // TODO: Find a way to store ptr/refs here
    shared_ptr<VertexLayout>    _vertexLayout;
    Vector<Uniform>             _vsUniforms;
    Vector<Uniform>             _fsUniforms;

    string _vsSource;
    string _fsSource;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static string VERTEX_COMPONENT(VertexComponent vComp);
    static string UNIFORM(Uniform uniform);
};

ENGINE_NAMESPACE_END
