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

struct VertexLayout {
    vector<VertexComponent> components;

    GLuint numComponents() const {
        GLuint totalComps = 0;
        for (VertexComponent component : components) {
            totalComps += component.components();
        }
        return totalComps;
    }

    GLuint bytesize() const {
        GLuint bytesize = 0;
        for (VertexComponent component : components) {
            bytesize += component.bytesize();
        }
        return bytesize;
    }

    bool operator==(const VertexLayout& o) const { return components == o.components; }
    bool operator!=(const VertexLayout& o) const { return !(*this == o); }
};

ENGINE_NAMESPACE_END
