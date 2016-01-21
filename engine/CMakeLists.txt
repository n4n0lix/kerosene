cmake_minimum_required(VERSION 3.2)
project(engine)

#######################################################
#                        CONFIG                       #
#######################################################

set(BUILD_TYPE release)
set(BUILD_OS   ${CMAKE_SYSTEM_NAME})
string(TOLOWER ${BUILD_OS} BUILD_OS)
set(BUILD_OS_ARCH "${BUILD_OS}${BUILD_ARCH}")
set(BUILD_ROOT "${PROJECT_SOURCE_DIR}/build")
set(BUILD_PATH "${BUILD_ROOT}/${BUILD_TYPE}/${BUILD_OS_ARCH}")

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

#######################################################
#                         CMAKE                       #
#######################################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/deps")

string(SUBSTRING ${BUILD_TYPE} 0  1 BUILD_TYPE_PRE)
string(SUBSTRING ${BUILD_TYPE} 1 -1 BUILD_TYPE_POST)
string(TOUPPER ${BUILD_TYPE_PRE} BUILD_TYPE_PRE)
string(TOLOWER ${BUILD_TYPE_POST} BUILD_TYPE_POST)
string(CONCAT _BUILD_TYPE ${BUILD_TYPE_PRE} ${BUILD_TYPE_POST})
set(CMAKE_BUILD_TYPE _BUILD_TYPE)

#######################################################
#                   HEADERS/SOURCES                   #
#######################################################

file(GLOB_RECURSE HEADERS "${SOURCE_PATH}/*.h")
file(GLOB_RECURSE SOURCES "${SOURCE_PATH}/*.cpp")

#######################################################
#                    EXPORT HEADERS                   #
#######################################################

file(COPY ${HEADERS} DESTINATION "${PROJECT_SOURCE_DIR}/include")

#######################################################
#                       COMPILE                       #
#######################################################
# glbinding
find_library(FOUND_GLBINDING glbinding "${PROJECT_SOURCE_DIR}/deps/glbinding")

# GLFW
#add_subdirectory("${PROJECT_SOURCE_DIR}/deps/glfw")

message("GLBINDING: " ${GLBINDING_INCLUDE_DIRS})
# ENGiNE
add_library(engine
        SHARED
        ${HEADERS}
        ${SOURCES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_definitions(-DENGINE_LIBRARY -DGLEW_STATIC)
set_target_properties(engine PROPERTIES PREFIX "")
include_directories(${GLFW_INCLUDE_DIRS} ${GLBINDING_INCLUDE_DIRS})
target_link_libraries(engine ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

#######################################################
#                     DEBUG OUTPUT                    #
#######################################################

message("Build")
message("   OS:   " ${BUILD_OS})
message("   Type: " ${BUILD_TYPE})
message("")
message("   Path: " ${BUILD_PATH})