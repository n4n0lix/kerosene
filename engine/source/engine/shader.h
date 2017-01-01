#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes
#include "logger.h"

// Internal Includes
#include "_global.h"
#include "map.h"

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
            ~Shader();

    bool operator==(const Shader& o) const;
    bool operator!=(const Shader& o) const;

    // TODO: Find a better way, this doesn't say that this shader is "smaller"
    bool operator<(const Shader& o1) const; // To be able to use in map

    void                     bind() const;
    Nullable<Uniform>        vertex_uniform(string name) const;
    Nullable<Uniform>        frag_uniform(string name) const;
    Nullable<TextureSlot>    frag_texture_slot(string name) const;
    shared_ptr<VertexLayout> get_vertex_layout() const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Shader();

    GLuint                    _id;
    shared_ptr<VertexLayout>  _vertexLayout;
    Vector<Uniform>           _vertexUniforms;
    Vector<Uniform>           _fragUniforms;
    Vector<TextureSlot>       _fragTextureSlots;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static GLuint CURRENT_SHADER;
    static Logger LOGGER;
};
ENGINE_NAMESPACE_END
