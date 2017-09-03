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
#include "engineexception.h"

#include "uniform.h"
#include "textureslot.h"
#include "vertex.h"
#include "shader.h"
#include "uniformtemplate.h"
#include "textureslottemplate.h"


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

    ShaderBuilder& vertex_uniform(string type, string name);
    ShaderBuilder& vertex_uniform(UniformTemplate uniform);

    ShaderBuilder& frag_uniform(string type, string name);
    ShaderBuilder& frag_uniform(UniformTemplate uniform);

    ShaderBuilder& frag_texture_slot(TextureSlotTemplate slot);


    // TODO: PerInstance Layout

    ShaderBuilder& vertex_source(string vscode);
    ShaderBuilder& frag_source(string fscode);

    owner<Shader>  build() const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   

    string                  gen_vertex_source() const;
    string                  gen_fragment_source() const;
    GLuint                  create_shader(GLenum shaderType) const;
    GLuint                  link_program(GLuint vertexShader, GLuint fragmentShader) const;
    list<Uniform>           process_uniforms(GLuint shaderId, const list<UniformTemplate>* uniforms) const;
    list<TextureSlot>       process_texture_slots(GLuint shaderId, const list<TextureSlotTemplate>* textureSlots) const;

    // TODO: Find a way to store ptr/refs here
    shared_ptr<VertexLayout>  _vertexLayout;
    list<UniformTemplate>     _vsUniforms;
    list<UniformTemplate>     _fsUniforms;
    list<TextureSlotTemplate> _fsTextureSlots;

    string _vsSource;
    string _fsSource;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static string VERTEX_COMPONENT(VertexComponent vComp);
    static string UNIFORM(UniformTemplate uniformTemplate);
    static string TEXTURE_SLOT(TextureSlotTemplate slot);
};

ENGINE_NAMESPACE_END
