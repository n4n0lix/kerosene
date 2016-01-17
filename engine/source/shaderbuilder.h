#ifndef SHADERBUILDER_H
#define SHADERBUILDER_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>
#include <sstream> 
    using std::ostringstream;
#include <vector>
    using std::vector;
#include <algorithm>

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"
#include "vertex.h"
#include "shader.h"
#include "engineexception.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DLL_PUBLIC ShaderBuilder
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit ShaderBuilder();

    ShaderBuilder& vertexlayout(VertexLayout layout);
    ShaderBuilder& uniform(Uniform uniform);

    // TODO: PerInstance Layout

    ShaderBuilder& vertex(string vscode);
    ShaderBuilder& fragment(string fscode);

    unique_ptr<Shader> build() const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   

    string gen_vs() const;
    string gen_fs() const;

    // TODO: Find a way to store ptr/refs here
    VertexLayout          _vertexLayout;
    vector<Uniform> _uniforms;

    string _vsSource;
    string _fsSource;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static string VERTEX_COMPONENT(VertexComponent vComp);
    static string UNIFORM(Uniform uniform);
};

ENGINE_NAMESPACE_END
#endif // SHADERBUILDER_H
