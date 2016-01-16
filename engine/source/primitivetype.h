#ifndef RENDERPRIMITIVETYPE
#define RENDERPRIMITIVETYPE

// Std-Includes

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          Enum                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

enum DLL_PUBLIC PrimitiveType {
    POINTS           = GL_POINTS,
    LINE             = GL_LINE,
    LINE_STRIP       = GL_LINE_STRIP,
    TRIANGLES        = GL_TRIANGLES,
    TRIANGLE_STRIP   = GL_TRIANGLE_STRIP,
};

ENGINE_NAMESPACE_END
#endif // RENDERPRIMITIVETYPE

