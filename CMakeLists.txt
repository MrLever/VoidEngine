cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

project(VoidEngine C CXX)

### Set build-configuration types
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

### Allow cmake to specify filters
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

### Set C++ flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("$<$<CONFIG:RELEASE>:/GL>")
add_compile_options("$<$<CONFIG:RELEASE>:/Ot>")
add_link_options("$<$<CONFIG:RELEASE>:/LTCG>")

### Set include directories
include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

### Add Dependencies to project
add_subdirectory(Dependencies/GLFW)
set_target_properties(glfw PROPERTIES FOLDER Dependencies/GLFW)
set_target_properties(uninstall PROPERTIES FOLDER Dependencies/GLFW)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_ZLIB OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Dependencies/assimp)
set_target_properties(assimp PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(IrrXML PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(zlib PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(zlibstatic PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER Dependencies/Assimp)

add_subdirectory(EngineCore)
add_subdirectory(EngineMath)
add_subdirectory(SuperVoid)