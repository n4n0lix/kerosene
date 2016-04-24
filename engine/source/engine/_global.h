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
#       ifdef COMPILER_MSVC
#           define INLINE   __forceinline
#       elif defined COMPILER_GCC
#           define INLINE   __attribute__((always_inline))
#       endif

// Namespace
#define ENGINE_NAMESPACE kerosene
#define ENGINE_NAMESPACE_BEGIN namespace kerosene {
#define ENGINE_NAMESPACE_END }

// Using std smart pointers
#include <memory>
        using std::unique_ptr;
        using std::make_unique;
        using std::shared_ptr;
        using std::make_shared;
        using std::weak_ptr;
        using std::move;
        using std::dynamic_pointer_cast;
        using std::static_pointer_cast;


// Using std primitives
#include <cstdint>
        using std::int32_t;  typedef int32_t  int32;
        using std::uint32_t; typedef uint32_t uint32;
        using std::int64_t;  typedef int64_t  int64;
        using std::uint64_t; typedef uint64_t uint64;




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

#include <map>
        using std::map;
        using std::pair;
        using std::make_pair;

#include <tuple>
        using std::tuple;
        using std::make_tuple;

// Define type sizes
#define FLOAT_BYTES 4
#define DOUBLE_BYTES 8
#define INT32_BYTES 4
#define INT64_BYTES 8
#define UINT32_BYTES 4
#define UINT64_BYTES 8