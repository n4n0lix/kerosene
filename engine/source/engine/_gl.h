#pragma once
#pragma warning(disable: 4005)

#include "_global.h"
#include "glew.h"
#include "glfw3.h"


#ifdef GL_DEBUG
    #include <string>
    #include <map> 
    #include "logger.h"
//std::cout << __FUNCTION__ << ":" << __LINE__ << "@" << #glFunc << "#\n";
    std::string gl_err_to_string(GLenum enm);

    #define printGLErrors(glFunc)                                                                   \
        {             \
          GLenum err;                                                                               \
          err = glGetError();                                                                       \
          if (err != GL_NO_ERROR) {                                                                 \
            std::cout << __FUNCTION__ << ":" << __LINE__ << "@" << #glFunc << "#" << ":" << "\n";   \
            std::cout << "    GL ERROR: " << gl_err_to_string(err) << "\n";                         \
            err = glGetError();                                                                     \
            DEBUG_TRIGGER                                                                           \
          }                                                                                         \
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

// A
// glActiveTexture
#ifdef GL_DEBUG
    #undef glActiveTexture
    #define glActiveTexture(...) \
    GLEW_GET_FUN(__glewActiveTexture)(__VA_ARGS__); \
    printGLErrors(glActiveTexture)
#elif GL_MOCK
    #undef glActiveTexture
    #define glActiveTexture(...) GLMock::invoking("glActiveTexture")
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

// glBindTexture
#ifdef GL_DEBUG
    #define glBindTexture(...) \
    glBindTexture(__VA_ARGS__); \
    printGLErrors(glBindTexture)
#elif GL_MOCK
    #define glBindTexture(...) GLMock::invoking("glBindTexture")
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
// glClear
#ifdef GL_DEBUG
    #undef glClear
    #define glClear(...) \
    glClear(__VA_ARGS__); \
    printGLErrors(glClear)
#elif GL_MOCK
    #undef glClear
    #define glClear(...) GLMock::invoking("glClear")
#endif

// glClearColor
#ifdef GL_DEBUG
    #undef glClearColor
    #define glClearColor(...) \
    glClearColor(__VA_ARGS__); \
    printGLErrors(glClearColor)
#elif GL_MOCK
    #undef glClearColor
    #define glClearColor(...) GLMock::invoking("glClearColor")
#endif

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
// glDeleteVertexArrays
#ifdef GL_DEBUG
#undef glDeleteVertexArrays
#define glDeleteVertexArrays(...) \
    GLEW_GET_FUN(__glewDeleteVertexArrays)(__VA_ARGS__); \
    printGLErrors(glDeleteVertexArrays)
#elif GL_MOCK
#undef glDeleteVertexArrays
#define glDeleteVertexArrays(...) GLMock::invoking("glDeleteVertexArrays")
#endif

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

// glDeleteTextures
#ifdef GL_DEBUG
#define glDeleteTextures(...) \
    glDeleteTextures(__VA_ARGS__); \
    printGLErrors(glDeleteTextures)
#elif GL_MOCK
#undef glDeleteTextures
#define glDeleteTextures(...) GLMock::invoking("glDeleteTextures")
#endif

// glDrawElements
#ifdef GL_DEBUG
    #define glDrawElements(...) \
    glDrawElements(__VA_ARGS__); \
    printGLErrors(glDrawElements)
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

// glGenerateMipmap
#ifdef GL_DEBUG
#undef glGenerateMipmap
#define glGenerateMipmap(...) \
    GLEW_GET_FUN(__glewGenerateMipmap)(__VA_ARGS__); \
    printGLErrors(glGenerateMipmap)
#elif GL_MOCK
#undef glGenerateMipmap
#define glGenerateMipmap(...) \
    GLMock::invoking("glGenerateMipmap")
#endif

// glGenTextures
#ifdef GL_DEBUG
    #define glGenTextures(...) \
    glGenTextures(__VA_ARGS__); \
    printGLErrors(glGenTextures)
#elif GL_MOCK
    #define glGenTextures(x, y) *y = 1; \
    GLMock::invoking("glGenTextures")
#endif

// glGenVertexArrays
#ifdef GL_DEBUG
#undef glGenVertexArrays
#define glGenVertexArrays(...) \
    GLEW_GET_FUN(__glewGenVertexArrays)(__VA_ARGS__); \
    printGLErrors(glGenVertexArrays)
#elif GL_MOCK
#undef glGenVertexArrays
#define glGenVertexArrays(...) GLMock::invoking("glGenVertexArrays")
#endif

// glGetUniformLocation
#ifdef GL_DEBUG
    #undef glGetUniformLocation
    #define glGetUniformLocation(...) \
    GLEW_GET_FUN(__glewGetUniformLocation)(__VA_ARGS__); \
    printGLErrors(glGetUniformLocation)
#elif GL_MOCK
    #undef glGetUniformLocation
    #define glGetUniformLocation(...) 1; GLMock::invoking("glGetUniformLocation")
#endif



// P
// glPixelStorei
#ifdef GL_DEBUG
#define glPixelStorei(...) \
    glPixelStorei(__VA_ARGS__); \
    printGLErrors(glPixelStorei)
#elif GL_MOCK
    #define glPixelStorei(x, y) GLMock::invoking("glPixelStorei")
#endif

// T
// glTexParameteri
#ifdef GL_DEBUG
    #define glTexParameteri(...) \
    glTexParameteri(__VA_ARGS__); \
    printGLErrors(glTexParameteri)
#elif GL_MOCK
    #define glTexParameteri(...) GLMock::invoking("glTexParameteri")
#endif

// glTexImage2D
#ifdef GL_DEBUG
    #define glTexImage2D(...) \
    glTexImage2D(__VA_ARGS__); \
    printGLErrors(glTexImage2D)
#elif GL_MOCK
    #define glTexImage2D(...) GLMock::invoking("glTexImage2D")
#endif


// U
// glUniform1i
#ifdef GL_DEBUG
#undef glUniform1i
#define glUniform1i(...) \
    GLEW_GET_FUN(__glewUniform1i)(__VA_ARGS__); \
    printGLErrors(glUniform1i)
#elif GL_MOCK
#undef glUniform1i
#define glUniform1i(...) GLMock::invoking("glUniform1i")
#endif

// glUseProgram
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
// glVertexAttribPointer
#ifdef GL_DEBUG
    #undef glVertexAttribPointer
    #define glVertexAttribPointer(...) \
    GLEW_GET_FUN(__glewVertexAttribPointer)(__VA_ARGS__); \
    printGLErrors(glVertexAttribPointer)
#elif GL_MOCK
    #undef glVertexAttribPointer
    #define glVertexAttribPointer(...) GLMock::invoking("glVertexAttribPointer")
#endif

// glViewport
#ifdef GL_DEBUG
#define glViewport(...) \
    glViewport(__VA_ARGS__); \
    printGLErrors(glViewport)
#elif GL_MOCK
#undef glViewport
#define glViewport(...) GLMock::invoking("glViewport")
#endif
