#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <sstream> 

// Other Includes
#include "logger.h"

// Internal Includes
#include "nullable.h"

#include "_global.h"
#include "perfstats.h"

#include "_gl.h"
#include "uniform.h"
#include "textureslot.h"

#include "vertex.h"
#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"
#include "matrix4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

enum class UniformType {
    VERTEX,
    FRAGMENT
};

class Shader
{
public:
            Shader(VertexLayout layout, vector<Uniform> vUniforms, vector<Uniform> fUniforms, vector<TextureSlot> texSlots, string vertex, string fragment);
            ~Shader();

    bool operator==( const Shader& o ) const;
    bool operator!=( const Shader& o ) const;
    
    bool operator<( const Shader& o1 ) const; // To be able to use in map

    void                    bind();
    Uniform                 vertex_uniform( string name );
    Uniform                 frag_uniform( string name );
    nullable<TextureSlot>   frag_texture_slot( string name );
    VertexLayout            get_vertex_layout();

    void                    set_vertex_uniform( Uniform uniform, const Matrix4f& mat4 );
    void                    set_vertex_uniform( Uniform uniform, const Vector2f& vec2 );
    void                    set_vertex_uniform( Uniform uniform, const Vector3f& vec3 );
    void                    set_vertex_uniform( Uniform uniform, const Vector4f& vec4 );

    void                    set_frag_uniform( Uniform uniform, const Matrix4f& mat4 );
    void                    set_frag_uniform( Uniform uniform, const Vector2f& vec2 );
    void                    set_frag_uniform( Uniform uniform, const Vector3f& vec3 );
    void                    set_frag_uniform( Uniform uniform, const Vector4f& vec4 );

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            GLuint                    _id;
            VertexLayout              _vertexLayout;
            map<string, Uniform>      _vertexUniforms;
            map<string, Uniform>      _fragUniforms;
            vector<TextureSlot>       _fragTextureSlots;

    void    set_uniform( Uniform uniform, const Matrix4f& mat4, map<string, Uniform>& uniforms );
    void    set_uniform( Uniform uniform, const Vector2f& vec2, map<string, Uniform>& uniforms );
    void    set_uniform( Uniform uniform, const Vector3f& vec3, map<string, Uniform>& uniforms );
    void    set_uniform( Uniform uniform, const Vector4f& vec4, map<string, Uniform>& uniforms );

    GLuint  create_vertex_shader( VertexLayout pLayout, vector<Uniform> pVUniforms, string pVertexSrc );
    GLuint  create_frag_shader( VertexLayout pLayout, vector<Uniform> pFUniforms, vector<TextureSlot> pTexSlots, string pFragSrc );
    GLuint  link_shader( GLuint pVShaderId, GLuint pFShaderId );
    map<string, Uniform> process_uniforms( vector<Uniform> pUniforms );
    vector<TextureSlot>  process_textureslots( vector<TextureSlot> pSlots );

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static GLuint CURRENT_SHADER;
    static Logger LOGGER;

    static string VERTEX_COMPONENT( VertexComponent vComp );
    static string UNIFORM( Uniform uniform );
    static string TEXTURE_SLOT( TextureSlot slot );

    static string GET_SHADER_LOG( GLuint pShaderId );
};

inline void Shader::bind()
{
    if ( CURRENT_SHADER != _id ) {
        glUseProgram( _id );
        CURRENT_SHADER = _id;
    }
}

inline void Shader::set_vertex_uniform( Uniform uniform, const Matrix4f & mat4 ) 
{ 
    set_uniform( uniform, mat4, _vertexUniforms ); 
}

inline void Shader::set_vertex_uniform( Uniform uniform, const Vector2f& vec2 ) 
{ 
    set_uniform( uniform, vec2, _vertexUniforms ); 
}

inline void Shader::set_vertex_uniform( Uniform uniform, const Vector3f& vec3 ) 
{ 
    set_uniform( uniform, vec3, _vertexUniforms ); 
}

inline void Shader::set_vertex_uniform( Uniform uniform, const Vector4f& vec4 ) 
{ 
    set_uniform( uniform, vec4, _vertexUniforms ); 
}

inline void Shader::set_frag_uniform( Uniform uniform, const Matrix4f& mat4 ) 
{
    set_uniform( uniform, mat4, _fragUniforms ); 
}

inline void Shader::set_frag_uniform( Uniform uniform, const Vector2f& vec2 ) 
{ 
    set_uniform( uniform, vec2, _fragUniforms ); 
}

inline void Shader::set_frag_uniform( Uniform uniform, const Vector3f& vec3 ) 
{ 
    set_uniform( uniform, vec3, _fragUniforms ); 
}

inline void Shader::set_frag_uniform( Uniform uniform, const Vector4f& vec4 ) 
{
    set_uniform( uniform, vec4, _fragUniforms ); 
}

inline void Shader::set_uniform( Uniform uniform, const Matrix4f& mat4, map<string, Uniform>& uniforms ) {
    vector<float> matrix = mat4.column_major();
    uint32        location = uniforms.find( uniform.gl_varname() )->second.gl_location();
    bind();
    glUniformMatrix4fv( location, 1, false, matrix.data() );
}

inline void Shader::set_uniform( Uniform uniform, const Vector2f& vec2, map<string, Uniform>& uniforms ) {
    uint32        location = uniforms.find( uniform.gl_varname() )->second.gl_location();
    bind();
    glUniform2f( location, vec2.x, vec2.y );
}

inline void Shader::set_uniform( Uniform uniform, const Vector3f& vec3, map<string, Uniform>& uniforms ) {
    uint32        location = uniforms.find( uniform.gl_varname() )->second.gl_location();
    bind();
    glUniform3f( location, vec3.x, vec3.y, vec3.z );
}

inline void Shader::set_uniform( Uniform uniform, const Vector4f& vec4, map<string, Uniform>& uniforms ) {
    uint32        location = uniforms.find( uniform.gl_varname() )->second.gl_location();
    bind();
    glUniform4f( location, vec4.x, vec4.y, vec4.z, vec4.w );
}

ENGINE_NAMESPACE_END
