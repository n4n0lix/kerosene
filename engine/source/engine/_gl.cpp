#include "_gl.h"

#ifdef GL_DEBUG

std::string gl_err_to_string(GLenum err) {
    switch (err) {
        case GL_INVALID_ENUM: return "Invalid enum.";
        case GL_INVALID_VALUE: return "Invalid value.";
        case GL_INVALID_OPERATION: return "Invalid operation.";
        case GL_STACK_OVERFLOW: return "Stack overflow.";
        case GL_STACK_UNDERFLOW: return "Stack underflow.";
        case GL_OUT_OF_MEMORY: return "Out of memory.";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation.";
        case GL_CONTEXT_LOST: return "Context lost.";
        case GL_TABLE_TOO_LARGE: return "Table too large.";
    }

    return "UNKOWN";
}

#endif

#ifdef GL_MOCK
std::map<std::string, std::uint32_t> GLMock::INVOCATIONS = std::map<std::string, std::uint32_t>();
#endif