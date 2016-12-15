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
#include "engineexception.h"
#include "vertex.h"
#include "shader.h"
#include "primitivetype.h"
#include "material.h"
#include "vertexarray.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class VERTEX>
class Batch
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
              explicit Batch(shared_ptr<Material> material);

    shared_ptr<VertexToken>             add_vertices(Vector<VERTEX> vertices);
    void                                remove_vertices(shared_ptr<VertexToken> token);
    
    void                                add_render_static(shared_ptr<VertexToken> token);
    void                                remove_render_static(shared_ptr<VertexToken> token);
    
    void                                set_view_matrix(Matrix4f viewMatrix);

    void                                render();

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    unique_ptr<VertexArray<VERTEX>> _vao;

    shared_ptr<Material> _material;
    shared_ptr<Shader>   _shader;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class VERTEX>
Batch<VERTEX>::Batch(shared_ptr<Material> material) {
    _material = material;
    _shader = material->get_shader();
    _vao = make_unique<VertexArray<VERTEX>>(_shader->get_vertex_layout());
}

template<class VERTEX>
shared_ptr<VertexToken> Batch<VERTEX>::add_vertices(Vector<VERTEX> vertices)
{
    return _vao->add_vertices( vertices );
}

template<class VERTEX>
void Batch<VERTEX>::remove_vertices(shared_ptr<VertexToken> token)
{
    _vao->remove_vertices( token );
}

template<class VERTEX>
void Batch<VERTEX>::add_render_static(shared_ptr<VertexToken> token)
{
    _vao->add_render_static( token );
}

template<class VERTEX>
void Batch<VERTEX>::remove_render_static(shared_ptr<VertexToken> token)
{
    _vao->remove_render_static(token);
}


template<class VERTEX>
void Batch<VERTEX>::render()
{
    _material->bind();
    _vao->render();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T>
Logger Batch<T>::LOGGER = Logger("Batch<>", Level::DEBUG);

ENGINE_NAMESPACE_END
