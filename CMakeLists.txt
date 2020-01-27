cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

################################################################################
# Require out-of-source builds
################################################################################
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

################################################################################
# Define project
################################################################################
project(VoidEngine C CXX)

################################################################################
# Set build-configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Allow cmake to generate Solution Folders
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Set project-wide C++ compile flags
################################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("$<$<CONFIG:RELEASE>:/GL>")
add_compile_options("$<$<CONFIG:RELEASE>:/Ot>")
add_link_options("$<$<CONFIG:RELEASE>:/LTCG>")

################################################################################
# Set project-wide include directories
################################################################################
include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

################################################################################
# Direct CMake to also build solutions for dependencies
################################################################################
## GLFW
add_subdirectory(Dependencies/GLFW)
set_target_properties(glfw PROPERTIES FOLDER Dependencies/GLFW)
set_target_properties(uninstall PROPERTIES FOLDER Dependencies/GLFW)

## Assimp
# Set Options
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_ZLIB OFF)
option(ASSIMP_BUILD_TESTS OFF)

# Add subdirectory
add_subdirectory(Dependencies/assimp)

# Configure project settings
set_target_properties(assimp PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(IrrXML PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(zlib PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(zlibstatic PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER Dependencies/Assimp)

## GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(Dependencies/googletest)
set_target_properties(gtest PROPERTIES FOLDER Dependencies/googletest)
set_target_properties(gtest_main PROPERTIES FOLDER Dependencies/googletest)
set_target_properties(gmock PROPERTIES FOLDER Dependencies/googletest)
set_target_properties(gmock_main PROPERTIES FOLDER Dependencies/googletest)

## Void Engine Components
add_subdirectory(EngineCore)
add_subdirectory(EngineMath)
add_subdirectory(SuperVoid)

## Test Suites
add_subdirectory(Tests)