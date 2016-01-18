#ifndef _RENDERDEFS_H
#define _RENDERDEFS_H

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <string>
        using std::string;

#include <vector>
        using std::vector;

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

struct DLL_PUBLIC VertexComponent {
    string type;
    string name;
    GLuint position;
    
    GLuint components() const {
        if (type == string("float")) {
            return 1;
        }
        else if (type == string("vec2")) {
            return 2;
        }
        else if (type == string("vec3")) {
            return 3;
        }
        else if (type == string("vec4")) {
            return 4;
        }

        return 0;
    }

    GLuint bytesize() const {
        if (type == string("float")) {
            return 1 * FLOAT_BYTES;
        }
        else if (type == string("vec2")) {
            return 2 * FLOAT_BYTES;
        }
        else if (type == string("vec3")) {
            return 3 * FLOAT_BYTES;
        }
        else if (type == string("vec4")) {
            return 4 * FLOAT_BYTES;
        }

        return 0;
    }

    GLenum gltype() {
        if (type == string("float") || type == string("vec2")
            || type == string("vec3") || type == string("vec4")) {
            return GL_FLOAT;
        }

        return GL_NONE;
    }

    bool operator==(const VertexComponent& o) const { return type == o.type && name == o.name && position == o.position; }
    bool operator!=(const VertexComponent& o) const { return !(*this == o); }
};

struct DLL_PUBLIC VertexLayout {
    vector<VertexComponent> comps;

    GLuint components() const {
        GLuint totalComps = 0;
        for (VertexComponent component : comps) {
            totalComps += component.components();
        }
        return totalComps;
    }

    GLuint bytesize() const {
        GLuint bytesize = 0;
        for (VertexComponent component : comps) {
            bytesize += component.bytesize();
        }
        return bytesize;
    }

    bool operator==(const VertexLayout& o) const { return comps == o.comps; }
    bool operator!=(const VertexLayout& o) const { return !(*this == o); }
};

struct DLL_PUBLIC Uniform {
    string  type;
    string  name;

    bool operator==(const Uniform& o) const { return type == o.type && name == o.name; }
    bool operator!=(const Uniform& o) const { return !(*this == o); }
};

struct DLL_PUBLIC TextureSlot {
    // TODO
};

ENGINE_NAMESPACE_END
#endif // _RENDERDEFS_H
