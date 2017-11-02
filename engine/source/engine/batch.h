#pragma once

// Other Includes

// Std-Includes
#include <algorithm>

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

class IBatch
{
public:

    virtual             ~IBatch() = default;
    virtual void                    remove_vertices( owner<VertexToken> token ) = 0;

    virtual void                    add_render( weak<VertexToken> token ) = 0;
    virtual void                    remove_render( weak<VertexToken> token ) = 0;

    virtual void                    set_wvp_matrix( Matrix4f wvpMatrix ) = 0;

    virtual void                    render() = 0;
};


template<class VERTEX>
class Batch : public IBatch
{
public:
            explicit Batch( weak<Material> material );
            virtual ~Batch() = default;

    owner<VertexToken>     add_vertices( std::vector<VERTEX>&& vertices );
    virtual void           remove_vertices( owner<VertexToken> token );

    virtual void           add_render( weak<VertexToken> token );
    virtual void           remove_render( weak<VertexToken> token );

    virtual void           set_wvp_matrix( Matrix4f viewMatrix );

    virtual void           render();

private:

    owner<VertexArray<VERTEX>> _vao;

    weak<Material> _material;
    Matrix4f       _wvp;

    static Logger LOGGER;
};


template<class VERTEX>
Batch<VERTEX>::Batch( weak<Material> material ) {
    if ( !material.is_ptr_valid() || material == nullptr ) throw std::exception( "Material is null!" );

    _material = material;
    _vao = make_owner<VertexArray<VERTEX>>();
}

template<class VERTEX>
owner<VertexToken> Batch<VERTEX>::add_vertices( std::vector<VERTEX>&& pVertices )
{
    return _vao->add_vertices( std::forward<std::vector<VERTEX>>( pVertices ) );
}

template<class VERTEX>
void Batch<VERTEX>::remove_vertices( owner<VertexToken> pToken )
{
    _vao->remove_vertices( std::move( pToken ) );
}

template<class VERTEX>
void Batch<VERTEX>::add_render( weak<VertexToken> pToken )
{
    _vao->add_render_static( pToken );
}

template<class VERTEX>
void Batch<VERTEX>::remove_render( weak<VertexToken> pToken )
{
    _vao->remove_render_static( pToken );
}

template<class VERTEX>
inline void Batch<VERTEX>::set_wvp_matrix( Matrix4f pWorldViewProj )
{
    _wvp = pWorldViewProj;
}

template<class VERTEX>
void Batch<VERTEX>::render()
{
    if ( _material.is_ptr_valid() ) {
        _material->bind();
        _material->get_shader()->set_vertex_uniform( Uniform::WORLD_VIEW_PROJ_MATRIX, _wvp );
    }

    _vao->render();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
Logger Batch<T>::LOGGER = Logger( "Batch<>", Level::DEBUG );

ENGINE_NAMESPACE_END
