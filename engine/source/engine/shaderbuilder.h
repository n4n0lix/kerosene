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
    ShaderBuilder& uniform(Uniform uniform);

    // TODO: PerInstance Layout

    ShaderBuilder& vertex(string vscode);
    ShaderBuilder& fragment(string fscode);

    unique_ptr<Shader> build() const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   

    string  genVertexSource() const;
    string  genFragmentSource() const;
    GLuint  createShader(GLenum shaderType) const;
    GLuint  linkProgram(GLuint vertexShader, GLuint fragmentShader) const;

    // TODO: Find a way to store ptr/refs here
    shared_ptr<VertexLayout>    _vertexLayout;
    vector<Uniform>             _uniforms;

    string _vsSource;
    string _fsSource;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static string VERTEX_COMPONENT(VertexComponent vComp);
    static string UNIFORM(Uniform uniform);
};

ENGINE_NAMESPACE_END
