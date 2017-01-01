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
class IBatch
{
public :

    virtual void                    remove_vertices(s_ptr<VertexToken> token) = 0;

    virtual void                    add_render(s_ptr<VertexToken> token)      = 0;
    virtual void                    remove_render(s_ptr<VertexToken> token)   = 0;

    virtual void                    set_view_matrix(Matrix4f viewMatrix)           = 0;

    virtual void                    render() = 0;
};

template<class VERTEX>
class Batch : public IBatch
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
              explicit Batch(s_ptr<Material> material);

            s_ptr<VertexToken>     add_vertices(Vector<VERTEX> vertices);
    virtual void                        remove_vertices(s_ptr<VertexToken> token);
    
    virtual void                        add_render(s_ptr<VertexToken> token);
    virtual void                        remove_render(s_ptr<VertexToken> token);
    
    virtual void                        set_view_matrix(Matrix4f viewMatrix);

    virtual void                        render();

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    unique_ptr<VertexArray<VERTEX>> _vao;

    s_ptr<Material> _material;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
    static Logger LOGGER;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class VERTEX>
Batch<VERTEX>::Batch(s_ptr<Material> material) {
    _material = material;
    _vao = make_unique<VertexArray<VERTEX>>(material->get_shader()->get_vertex_layout());
}

template<class VERTEX>
s_ptr<VertexToken> Batch<VERTEX>::add_vertices(Vector<VERTEX> vertices)
{
    return _vao->add_vertices( vertices );
}

template<class VERTEX>
void Batch<VERTEX>::remove_vertices(s_ptr<VertexToken> token)
{
    _vao->remove_vertices( token );
}

template<class VERTEX>
void Batch<VERTEX>::add_render(s_ptr<VertexToken> token)
{
    _vao->add_render_static( token );
}

template<class VERTEX>
void Batch<VERTEX>::remove_render(s_ptr<VertexToken> token)
{
    _vao->remove_render_static(token);
}

template<class VERTEX>
inline void Batch<VERTEX>::set_view_matrix(Matrix4f viewMatrix)
{
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
