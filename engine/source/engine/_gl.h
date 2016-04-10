#pragma once
#include "glew.h"

#ifdef ENGINE_DEBUG
    #pragma warning(disable: 4005)
    #include "logger.h"

    // SHADER

    #define glUseProgram(...) \
    GLEW_GET_FUN(__glewUseProgram)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glUseProgram")

    // VAO

    #define glBindVertexArray(...) \
    GLEW_GET_FUN(__glewBindVertexArray)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glBindVertexArray")

    // BUFFER

    #define glGenBuffers(...) \
    GLEW_GET_FUN(__glewGenBuffers)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glGenBuffers")

    #define glDeleteBuffers(...) \
    GLEW_GET_FUN(__glewDeleteBuffers)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glDeleteBuffers")

    #define glBindBuffer(...) \
    GLEW_GET_FUN(__glewBindBuffer)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glBindBuffer")

    #define glBufferData(...) \
    GLEW_GET_FUN(__glewBufferData)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glBufferData")

    #define glBufferSubData(...) \
    GLEW_GET_FUN(__glewBufferSubData)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glBufferSubData")

    #define glCopyBufferSubData(...) \
    GLEW_GET_FUN(__glewCopyBufferSubData)(__VA_ARGS__); \
    Logger::glerr(__FUNCTION__, __LINE__, "glCopyBufferSubData")


#endif