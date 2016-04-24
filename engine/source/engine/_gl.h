#pragma once
#pragma warning(disable: 4005)

#include "glew.h"
#include "glfw3.h"

#ifdef GL_DEBUG
    #include <string>
    #include <map> 
    #include "logger.h"

    std::string gl_err_to_string(GLenum enm);

    #define printGLErrors(glFunc)                                                               \
        { GLenum err;                                                                           \
          err = glGetError();                                                                   \
          if (err != GL_NO_ERROR) {                                                             \
            std::cerr << __FUNCTION__ << ":" << __LINE__ << "@" << "#glFunc##" << ":" << endl;  \
            while (err != GL_NO_ERROR) {                                                        \
                            std::cerr << "    GL ERROR: " << gl_err_to_string(err) << endl;     \
                            err = glGetError();                                                 \
                    }                                                                           \
            }                                                                                   \
        }
#endif

#ifdef GL_MOCK
    #include <memory>
    #include <map>
    #include <cstdint>
    #include <iostream>

    class GLMock {
    public:
        static void invoking(std::string name) {
            INVOCATIONS[name]++;
        }

        static std::uint32_t invocations(std::string name) {
            return INVOCATIONS[name];
        }

        static void reset() {
            INVOCATIONS.clear();
        }

    private:
        static std::map<std::string, std::uint32_t> INVOCATIONS;
    };
#endif

// B
// glBindBuffer
#ifdef GL_DEBUG
    #undef glBindBuffer
    #define glBindBuffer(...) \
    GLEW_GET_FUN(__glewBindBuffer)(__VA_ARGS__); \
    printGLErrors(glBindBuffer)
#elif GL_MOCK
    #undef glBindBuffer
    #define glBindBuffer(...) GLMock::invoking("glBindBuffer")
#endif

// glBufferData
#ifdef GL_DEBUG
    #undef glBufferData
    #define glBufferData(...) \
    GLEW_GET_FUN(__glewBufferData)(__VA_ARGS__); \
    printGLErrors(glBufferData)
#elif GL_MOCK
    #undef glBufferData
    #define glBufferData(...) GLMock::invoking("glBufferData")
#endif

// glBufferSubData
#ifdef GL_DEBUG
    #undef glBufferSubData
    #define glBufferSubData(...) \
    GLEW_GET_FUN(__glewBufferSubData)(__VA_ARGS__); \
    printGLErrors(glBufferSubData)
#elif GL_MOCK
    #undef glBufferSubData
    #define glBufferSubData(...) GLMock::invoking("glBufferSubData")
#endif

// glBindVertexArray
#ifdef GL_DEBUG
    #undef glBindVertexArray
    #define glBindVertexArray(...) \
    GLEW_GET_FUN(__glewBindVertexArray)(__VA_ARGS__); \
    printGLErrors(glBindVertexArray)
#elif GL_MOCK
    #undef glBindVertexArray
    #define glBindVertexArray(...) GLMock::invoking("glBindVertexArray")
#endif

// C
// glCopyBufferSubData
#ifdef GL_DEBUG
    #undef glCopyBufferSubData
    #define glCopyBufferSubData(...) \
    GLEW_GET_FUN(__glewCopyBufferSubData)(__VA_ARGS__); \
    printGLErrors(glCopyBufferSubData)
#elif GL_MOCK
    #undef glCopyBufferSubData
    #define glCopyBufferSubData(...) GLMock::invoking("glCopyBufferSubData")
#endif

// D
// glDeleteBuffers
#ifdef GL_DEBUG
    #undef glDeleteBuffers
    #define glDeleteBuffers(...) \
    GLEW_GET_FUN(__glewDeleteBuffers)(__VA_ARGS__); \
    printGLErrors(glDeleteBuffers)
#elif GL_MOCK
    #undef glDeleteBuffers
    #define glDeleteBuffers(...) GLMock::invoking("glDeleteBuffers")
#endif

// glDrawElements
#ifdef GL_DEBUG
#define glDrawElements(...) \
    glDrawElements(__VA_ARGS__); \
    printGLErrors(glDeleteBuffers)
#elif GL_MOCK
    #define glDrawElements(...) GLMock::invoking("glDrawElements")
#endif

// E
#ifdef GL_DEBUG
    #undef glEnableVertexAttribArray
    #define glEnableVertexAttribArray(...) \
    GLEW_GET_FUN(__glewEnableVertexAttribArray)(__VA_ARGS__); \
    printGLErrors(glEnableVertexAttribArray)
#elif GL_MOCK
    #undef glEnableVertexAttribArray
    #define glEnableVertexAttribArray(...) GLMock::invoking("glEnableVertexAttribArray")
#endif
    
// G
// glGenBuffers
#ifdef GL_DEBUG
    #undef glGenBuffers
    #define glGenBuffers(...) \
    GLEW_GET_FUN(__glewGenBuffers)(__VA_ARGS__); \
    printGLErrors(glGenBuffers)
#elif GL_MOCK
    #undef glGenBuffers
    #define glGenBuffers(x, y) *y = 1; \
    GLMock::invoking("glGenBuffers")
#endif

// U
#ifdef GL_DEBUG
    #undef glUseProgram
    #define glUseProgram(...) \
    GLEW_GET_FUN(__glewUseProgram)(__VA_ARGS__); \
    printGLErrors(glUseProgram)
#elif GL_MOCK
    #undef glUseProgram
    #define glUseProgram(...) GLMock::invoking("glUseProgram")
#endif

// V
#ifdef GL_DEBUG
    #undef glVertexAttribPointer
    #define glVertexAttribPointer(...) \
    GLEW_GET_FUN(__glewVertexAttribPointer)(__VA_ARGS__); \
    printGLErrors(glVertexAttribPointer)
#elif GL_MOCK
    #undef glVertexAttribPointer
    #define glVertexAttribPointer(...) GLMock::invoking("glVertexAttribPointer")
#endif
