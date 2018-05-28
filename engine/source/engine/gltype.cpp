#include "stdafx.h"
#include "gltype.h"

ENGINE_NAMESPACE_BEGIN

GLType GLType::FLOAT = GLType( 0, 1, 1 * FLOAT_BYTES );
GLType GLType::VEC2  = GLType( 1, 2, 2 * FLOAT_BYTES );
GLType GLType::VEC3  = GLType( 2, 3, 3 * FLOAT_BYTES );
GLType GLType::VEC4  = GLType( 3, 4, 4 * FLOAT_BYTES );
GLType GLType::MAT4  = GLType( 4, 16, 16 * FLOAT_BYTES );

ENGINE_NAMESPACE_END
