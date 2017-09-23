#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <sstream> 

// Other Includes
#include "logger.h"

// Internal Includes
#include "_global.h"
#include "nullable.h"

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

enum UniformType {
    VERTEX,
    FRAGMENT
};

class Shader
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static void     bind( GLuint shaderId );

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Shader(VertexLayout layout, vector<Uniform> vUniforms, vector<Uniform> fUniforms, vector<TextureSlot> texSlots, string vertex, string fragment);
            ~Shader();

    bool operator==( const Shader& o ) const;
    bool operator!=( const Shader& o ) const;
    
    // TODO: Find a better way, this doesn't say that this shader is "smaller"
    bool operator<( const Shader& o1 ) const; // To be able to use in map

    inline void              bind();
    Uniform                  vertex_uniform( string name );
    Uniform                  frag_uniform( string name );
    Nullable<TextureSlot>    frag_texture_slot( string name );
    VertexLayout             get_vertex_layout();

    inline void              set_vertex_uniform( const Uniform& uniform, const Matrix4f& mat4 );
    inline void              set_vertex_uniform( const Uniform& uniform, const Vector2f& vec2 );
    inline void              set_vertex_uniform( const Uniform& uniform, const Vector3f& vec3 );
    inline void              set_vertex_uniform( const Uniform& uniform, const Vector4f& vec4 );

    inline void              set_frag_uniform( const Uniform& uniform, const Matrix4f& mat4 );
    inline void              set_frag_uniform( const Uniform& uniform, const Vector2f& vec2 );
    inline void              set_frag_uniform( const Uniform& uniform, const Vector3f& vec3 );
    inline void              set_frag_uniform( const Uniform& uniform, const Vector4f& vec4 );

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            GLuint                    _id;
            VertexLayout              _vertexLayout;
            map<string, Uniform>      _vertexUniforms;
            map<string, Uniform>      _fragUniforms;
            vector<TextureSlot>       _fragTextureSlots;

    inline void    set_uniform( const Uniform& uniform, const Matrix4f& mat4, const map<string, Uniform>& uniforms );
    inline void    set_uniform( const Uniform& uniform, const Vector2f& vec2, const map<string, Uniform>& uniforms );
    inline void    set_uniform( const Uniform& uniform, const Vector3f& mat4, const map<string, Uniform>& uniforms );
    inline void    set_uniform( const Uniform& uniform, const Vector4f& vec2, const map<string, Uniform>& uniforms );

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
ENGINE_NAMESPACE_END
