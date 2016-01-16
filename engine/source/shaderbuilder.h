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

    ShaderBuilder& uni(ShaderUniform uniform);
    ShaderBuilder& in(ShaderLocation location);

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
    vector<ShaderUniform>  _uniforms;
    vector<ShaderLocation> _locations;

    string _vsSource;
    string _fsSource;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static string LOCATION_IN(ShaderLocation location);
    static string UNIFORM(ShaderUniform uniform);
};

ENGINE_NAMESPACE_END
#endif // SHADERBUILDER_H
