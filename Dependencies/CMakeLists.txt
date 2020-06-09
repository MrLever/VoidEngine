################################################################################
# Include and configure dependencies
################################################################################
## GLFW
add_subdirectory(GLFW)
set_target_properties(glfw PROPERTIES FOLDER Engine/Dependencies/GLFW)
set_target_properties(uninstall PROPERTIES FOLDER Engine/Dependencies/GLFW)

## Assimp
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_ZLIB OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(assimp)
set_target_properties(assimp PROPERTIES FOLDER Engine/Dependencies/Assimp)
set_target_properties(IrrXML PROPERTIES FOLDER Engine/Dependencies/Assimp)
set_target_properties(zlib PROPERTIES FOLDER Engine/Dependencies/Assimp)
set_target_properties(zlibstatic PROPERTIES FOLDER Engine/Dependencies/Assimp)
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER Engine/Dependencies/Assimp)

## GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

option(BUILD_GMOCK OFF)
add_subdirectory(googletest)
set_target_properties(gtest PROPERTIES FOLDER Engine/Dependencies/googletest)
set_target_properties(gtest_main PROPERTIES FOLDER Engine/Dependencies/googletest)