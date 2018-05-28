#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <typeinfo>

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "noncopyable.h"
#include "vertexlayout.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

template<typename VERTEX>
class GLVAO : public noncopyable
{
public:
    // Enabled:
    GLVAO();             // Constructor
    ~GLVAO() = default;  // Destructor

protected:
    void             native_create();
    void             native_bind();
    void             native_delete();
    void             native_unbind();

    const uint32&          id();
    const VertexLayout&    layout();

private:
    GLuint       _id;
    VertexLayout _layout;

    static Logger LOGGER;
};

template<typename VERTEX>
GLVAO<VERTEX>::GLVAO()
{
    VERTEX v;
    _layout = v.layout;
}

template<class VERTEX>
void GLVAO<VERTEX>::native_create()
{
    glGenVertexArrays( 1, &_id );

    glBindVertexArray( _id );
    for ( VertexComponent component : _layout.components() ) {
        glEnableVertexAttribArray( component.position );
    }
    glBindVertexArray( 0 );
}

template<class VERTEX>
void GLVAO<VERTEX>::native_delete()
{
    glDeleteVertexArrays( 1, &_id );
}

template<class VERTEX>
void GLVAO<VERTEX>::native_bind()
{
    glBindVertexArray( _id );
}

template<class VERTEX>
void GLVAO<VERTEX>::native_unbind()
{
    glBindVertexArray( 0 );
}

template<typename VERTEX>
const uint32 & GLVAO<VERTEX>::id()
{
    return _id;
}

template<typename VERTEX>
const VertexLayout& GLVAO<VERTEX>::layout()
{
    return _layout;
}

template<typename VERTEX>
Logger GLVAO<VERTEX>::LOGGER = Logger( string("GLVAO<") + string(typeid(VERTEX).name()) + string(">"), Level::DEBUG );

ENGINE_NAMESPACE_END

