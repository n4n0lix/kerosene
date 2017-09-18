#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

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

class Shader
{
    friend class ShaderBuilder;
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static void     bind( GLuint shaderId );

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Shader();
            ~Shader();

    bool operator==( const Shader& o ) const;
    bool operator!=( const Shader& o ) const;

    // TODO: Find a better way, this doesn't say that this shader is "smaller"
    bool operator<( const Shader& o1 ) const; // To be able to use in map

    void                     bind();
    Nullable<Uniform>        vertex_uniform( string name );
    Nullable<Uniform>        frag_uniform( string name );
    Nullable<TextureSlot>    frag_texture_slot( string name );
    VertexLayout             get_vertex_layout();

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    GLuint                    _id;
    VertexLayout              _vertexLayout;
    vector<Uniform>           _vertexUniforms;
    vector<Uniform>           _fragUniforms;
    vector<TextureSlot>       _fragTextureSlots;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static GLuint CURRENT_SHADER;
    static Logger LOGGER;
};
ENGINE_NAMESPACE_END
