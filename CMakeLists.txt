cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

project(SuperVoid C CXX)

### Set build-configuration types
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

### Set C++ flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("$<$<CONFIG:RELEASE>:/GL>")
add_compile_options("$<$<CONFIG:RELEASE>:/Ot>")
add_link_options("$<$<CONFIG:RELEASE>:/LTCG>")


### Allow cmake to specify filters
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

### Add Dependencies to project
add_subdirectory(Dependencies/GLFW)
#add_subdirectory(Dependencies/assimp)


#add_subdirectory(EngineCore)
add_subdirectory(EngineMath)
#add_subdirectory(SuperVoid)

