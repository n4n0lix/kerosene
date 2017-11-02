#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "vertexcomponent.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class VertexLayout {
private:
    uint32 _numComps;
    uint32 _bytesize;
    std::vector<VertexComponent> _components;

public:
            VertexLayout() { }

    explicit VertexLayout( std::vector<VertexComponent> comps ) : _components( comps ) {
        _numComps = 0;
        _bytesize = 0;

        for ( VertexComponent component : _components ) {
            _numComps += component.num_components();
            _bytesize += component.bytesize();
        }
    }

            ~VertexLayout() = default;

    std::vector<VertexComponent> components() const {
        return _components;
    }

    uint32 num_components() const {
        return _numComps;
    }

    uint32 bytesize() const {
        return _bytesize;
    }

    bool operator==( const VertexLayout& o ) const { return _components == o._components; }
    bool operator!=( const VertexLayout& o ) const { return !(*this == o); }

};

ENGINE_NAMESPACE_END
