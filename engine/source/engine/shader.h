#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <vector>
    using std::vector;

// Other Includes
#include "logger.h"

// Internal Includes
#include "_global.h"
#include "_gl.h"
#include "_renderdefs.h"

#include "vertex.h"
#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class DLL_PUBLIC Shader
{
    friend class ShaderBuilder;
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // Uniform
    static Uniform  Uni_WVP;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    bool operator==(const Shader& o) const;
    bool operator!=(const Shader& o) const;

    // TODO: Find a better way, this doesn't say that this shader is "smaller"
    bool operator<(const Shader& o1) const; // To be able to use in map

    void                     bind() const;
    shared_ptr<VertexLayout> getVertexLayout() const;

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Shader();

    GLuint                    _id;
    shared_ptr<VertexLayout>  _vertexLayout;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static GLuint CURRENT_SHADER;
    static Logger LOGGER;
};
ENGINE_NAMESPACE_END