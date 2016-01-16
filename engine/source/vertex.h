#ifndef VERTEX_H
#define VERTEX_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

// Position
#define VERTEX_POSITION_COMPONENTS  VECTOR3F_COMPONENTS;
#define VERTEX_POSITION_OFFSET      0;

// Color
#define VERTEX_COLOR_COMPONENTS     VECTOR4F_COMPONENTS;
#define VERTEX_COLOR_OFFSET         VERTEX_POSITION_OFFSET + VECTOR3F_BYTES;

// TexCoords
#define VERTEX_TEXCOORDS_COMPONENTS VECTOR2F_COMPONENTS;
#define VERTEX_TEXCOORDS_OFFSET     VERTEX_COLOR_OFFSET + VECTOR2F_BYTES;

// General
#define VERTEX_COMPONENTS           (VERTEX_POSITION_COMPONENTS + VERTEX_COLOR_COMPONENTS + VERTEX_TEXCOORDS_COMPONENTS)
#define VERTEX_BYTES                VECTOR3F_BYTES + VECTOR4F_BYTES + VECTOR2F_BYTES

class DLL_PUBLIC Vertex
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Vertex();

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



};

ENGINE_NAMESPACE_END
#endif // VERTEX_H
