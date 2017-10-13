#pragma once

#pragma warning(disable: 4251)
#pragma warning(disable: 4275)

////////////////////////////////////////////////////////////////////////////
//                            Operating System                            //
////////////////////////////////////////////////////////////////////////////

// WINDOWS
#if (defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)) && !(defined(_WIN64) && !defined(__WIN64) && !defined(__WIN64__))
#   define OS_WIN32
#endif

#if defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)
#   define OS_WIN64
#endif

#if defined(OS_WIN32) || defined(OS_WIN64)
#   define OS_WIN
#endif

// UNIX
#ifdef __linux__
#   define OS_LINUX
#endif

////////////////////////////////////////////////////////////////////////////
//                                Compiler                                //
////////////////////////////////////////////////////////////////////////////

// MSVC
#ifdef _MSC_VER
#   define COMPILER_MSVC
#endif

// GCC
#ifdef __GNUC__
#   define COMPILER_GCC
#endif

// CLANG
#ifdef __clang__
#   define COMPILER_CLANG
#endif

//
// DLL
//
#ifdef OS_WIN
#   ifdef ENGINE_LIBRARY
#       ifdef COMPILER_MSVC
#           define DLL_PUBLIC   __declspec(dllexport)
#           define DLL_PRIVATE
#       elif defined COMPILER_GCC
#           define DLL_PUBLIC   __attribute__((dllexport))
#           define DLL_PRIVATE
#       endif
#   elif ENGINE_EXEC
#       ifdef COMPILER_MSVC
#           define DLL_PUBLIC   __declspec(dllimport)
#           define DLL_PRIVATE
#       elif defined COMPILER_GCC
#           define DLL_PUBLIC   __attribute__((dllimport))
#           define DLL_PRIVATE
#       endif
#   else
#       ifdef COMPILER_MSVC
#           define DLL_PUBLIC
#           define DLL_PRIVATE
#       elif defined COMPILER_GCC
#           define DLL_PUBLIC
#           define DLL_PRIVATE
#       endif
#   endif
#elif defined OS_LINUX
#   ifdef ENGINE_LIBRARY
#       ifdef COMPILER_GCC
#           define DLL_PUBLIC  __attribute__ ((visibility ("default")))
#           define DLL_PRIVATE __attribute__ ((visibility ("hidden")))
#       endif
#   else
#       ifdef COMPILER_GCC
#           define DLL_PUBLIC
#           define DLL_PRIVATE
#       endif
#   endif
#endif

// COMPILER DEPENDENT STUFF
#include <signal.h>

#       ifdef COMPILER_MSVC
#           define INLINE           __forceinline
#           define DEBUG_TRIGGER    __debugbreak();
#       elif defined COMPILER_GCC
#           define INLINE   __attribute__((always_inline))
#           define DEBUG_TRIGGER    raise(SIGTRAP)
#       endif


// DEBUG TRIGGER


// Namespace
#define ENGINE_NAMESPACE kerosene
#define ENGINE_NAMESPACE_BEGIN namespace kerosene {
#define ENGINE_NAMESPACE_END }

// Preprocessor
#define STRINGIFY(x) #x


// Ownership management
#include "object.h"
#include "owner.h"
#include <memory>
        using std::shared_ptr;
        using std::make_shared;
        using std::make_unique;
        using std::dynamic_pointer_cast;
        using std::static_pointer_cast;

        template <typename T>
        using unique = std::unique_ptr<T>;

        template <typename T> 
        using shared = std::shared_ptr<T>;

// Using std primitives
#include <cstdint>
        using std::size_t;
        using std::int8_t;   typedef int8_t   int8;
        using std::uint8_t;  typedef uint8_t  uint8;
        using std::int16_t;  typedef int16_t  int16;
        using std::uint16_t; typedef uint16_t uint16;
        using std::int32_t;  typedef int32_t  int32;
        using std::uint32_t; typedef uint32_t uint32;
        using std::int64_t;  typedef int64_t  int64;
        using std::uint64_t; typedef uint64_t uint64;

        typedef unsigned char byte;
        typedef char16_t      char16;
        typedef char32_t      char32;

#include <chrono>
using namespace std::chrono_literals;

        typedef std::chrono::milliseconds milliseconds;
        typedef std::chrono::seconds      seconds;

// Using cout
#include <iostream>
        using std::cout;
        using std::endl;

// Using std string
#include <string>
        using std::string;

// Using atomic
#include <atomic>
        using std::atomic;

// Using collections
#include <vector>
        using std::vector;

#include <queue>
        using std::queue;

#include <map>
        using std::map;
        using std::pair;
        using std::make_pair;

#include <tuple>
        using std::tuple;
        using std::make_tuple;

// Using functional programming
#include <functional>
        using std::function;

// Guards
#define Guard(x) if (!(x))

// Using assertions
#include <cassert>
#include <type_traits>

#define StaticAssert(cond) static_assert(cond, "Static Type Assertion failure at" __FILE__ ": " STRINGIFY(__LINE__));

#if defined(CONTRACTS_ENABLED)
#   define Requires(cond)  if (!(cond)) \
    throw std::runtime_error("Precondition failure at " __FILE__ ": " STRINGIFY(__LINE__));
#   define Assert(cond)  if (!(cond)) \
    throw std::runtime_error("Inline Assertion failure at " __FILE__ ": " STRINGIFY(__LINE__));
#   define Ensures(cond)  if (!(cond)) \
    throw std::runtime_error("Postcondition failure at " __FILE__ ": " STRINGIFY(__LINE__));
#else
#   define Requires(cond)   
#   define Assert(cond)
#   define Ensures(cond)           
#endif 

// Define type sizes
#define FLOAT_BYTES 4
#define DOUBLE_BYTES 8
#define INT16_BYTES 2
#define INT32_BYTES 4
#define INT64_BYTES 8
#define UINT16_BYTES 2
#define UINT32_BYTES 4
#define UINT64_BYTES 8

// Define type min/max
#include <limits>
#define MIN(X) __min_of(X)
template<typename T>
inline T __min_of( T& val ) {
    return std::numeric_limits<T>::min();
}

#define MAX(X) __max_of(X)
template<typename T>
inline T __max_of( T& val ) {
    return std::numeric_limits<T>::max();
}

// MEMORY LEAK DETECTION
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif