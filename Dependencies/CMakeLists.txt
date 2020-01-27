################################################################################
# Include and configure dependencies
################################################################################
## GLFW
add_subdirectory(GLFW)
set_target_properties(glfw PROPERTIES FOLDER Dependencies/GLFW)
set_target_properties(uninstall PROPERTIES FOLDER Dependencies/GLFW)

## Assimp
# Set Options
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_ZLIB OFF)
option(ASSIMP_BUILD_TESTS OFF)

# Add subdirectory
add_subdirectory(assimp)

# Configure project settings
set_target_properties(assimp PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(IrrXML PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(zlib PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(zlibstatic PROPERTIES FOLDER Dependencies/Assimp)
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER Dependencies/Assimp)

## GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest)
set_target_properties(gtest PROPERTIES FOLDER Dependencies/googletest)
set_target_properties(gtest_main PROPERTIES FOLDER Dependencies/googletest)
set_target_properties(gmock PROPERTIES FOLDER Dependencies/googletest)
set_target_properties(gmock_main PROPERTIES FOLDER Dependencies/googletest)