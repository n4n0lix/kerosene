#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <algorithm>
using std::transform;

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "_renderdefs.h"
#include "logger.h"
#include "vertex.h"
#include "shader.h"
#include "primitivetype.h"
#include "material.h"
#include "vertexarray.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class IBatch
{
public:

    virtual             ~IBatch() = default;
    virtual void                    remove_vertices( owner<VertexToken> token ) = 0;

    virtual void                    add_render( weak<VertexToken> token ) = 0;
    virtual void                    remove_render( weak<VertexToken> token ) = 0;

    virtual void                    set_view_matrix( Matrix4f viewMatrix ) = 0;

    virtual void                    render() = 0;
};

template<class VERTEX>
class Batch : public IBatch
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            explicit Batch( weak<Material> material );
            virtual ~Batch() = default;

    owner<VertexToken>     add_vertices( vector<VERTEX>&& vertices );
    virtual void           remove_vertices( owner<VertexToken> token );

    virtual void           add_render( weak<VertexToken> token );
    virtual void           remove_render( weak<VertexToken> token );

    virtual void           set_view_matrix( Matrix4f viewMatrix );

    virtual void           render();

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    owner<VertexArray<VERTEX>> _vao;

    weak<Material> _material;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class VERTEX>
Batch<VERTEX>::Batch( weak<Material> material ) {
    if ( !material.ptr_is_valid() || material == nullptr ) throw std::exception( "Material is null!" );

    _material = material;
    _vao = make_owner<VertexArray<VERTEX>>( material->get_shader()->get_vertex_layout() );
}

template<class VERTEX>
owner<VertexToken> Batch<VERTEX>::add_vertices( vector<VERTEX>&& vertices )
{
    return _vao->add_vertices( std::forward<vector<VERTEX>>( vertices ) );
}

template<class VERTEX>
void Batch<VERTEX>::remove_vertices( owner<VertexToken> token )
{
    _vao->remove_vertices( std::move( token ) );
}

template<class VERTEX>
void Batch<VERTEX>::add_render( weak<VertexToken> token )
{
    _vao->add_render_static( token );
}

template<class VERTEX>
void Batch<VERTEX>::remove_render( weak<VertexToken> token )
{
    _vao->remove_render_static( token );
}

template<class VERTEX>
inline void Batch<VERTEX>::set_view_matrix( Matrix4f viewMatrix )
{
}

template<class VERTEX>
void Batch<VERTEX>::render()
{
    if ( _material.ptr_is_valid() ) {
        _material->bind();
    }

    _vao->render();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
Logger Batch<T>::LOGGER = Logger( "Batch<>", Level::DEBUG );

ENGINE_NAMESPACE_END
