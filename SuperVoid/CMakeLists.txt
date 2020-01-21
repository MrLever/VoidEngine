project(SuperVoid CXX)

################################################################################
# Source groups
################################################################################
set(Header_Files__Entities
    "BouncingCube.h"
    "PlayerShip.h"
)
source_group("Header Files\\Entities" FILES ${Header_Files__Entities})

set(Source_Files
    "Core.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Entities
    "BouncingCube.cpp"
    "PlayerShip.cpp"
)
source_group("Source Files\\Entities" FILES ${Source_Files__Entities})

set(ALL_FILES
    ${Header_Files__Entities}
    ${Source_Files}
    ${Source_Files__Entities}
)

### Specify target type
add_executable(${PROJECT_NAME} ${ALL_FILES})
set(ROOT_NAMESPACE SuperVoid)


### Specify library dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
    EngineCore
    EngineMath
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "assimp-vc142-mtd"
        ">"
        "$<$<CONFIG:Release>:"
            "assimp-vc142-mt"
        ">"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")



























project(SuperVoid CXX)

################################################################################
# Source groups
################################################################################
set(Header_Files__Entities
    "BouncingCube.h"
    "PlayerShip.h"
)
source_group("Header Files\\Entities" FILES ${Header_Files__Entities})

set(Source_Files
    "Core.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Entities
    "BouncingCube.cpp"
    "PlayerShip.cpp"
)
source_group("Source Files\\Entities" FILES ${Source_Files__Entities})

set(ALL_FILES
    ${Header_Files__Entities}
    ${Source_Files}
    ${Source_Files__Entities}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SuperVoid)

################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "_MBCS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "_MBCS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                ${DEFAULT_CXX_RUNTIME_LIBRARY};
                /Gy
            >
            /permissive-;
            /std:c++latest;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                ${DEFAULT_CXX_RUNTIME_LIBRARY};
                /Gy
            >
            /permissive-;
            /std:c++latest;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /NODEFAULTLIB:msvcrtd.lib;
                /OPT:REF;
                /LTCG;
                /OPT:ICF
            >
            /DEBUG:FULL;
            /SUBSYSTEM:CONSOLE;
            /WHOLEARCHIVE:EngineCore.lib
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /NODEFAULTLIB:msvcrtd.lib;
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG:FULL;
            /SUBSYSTEM:CONSOLE;
            /WHOLEARCHIVE:EngineCore.lib
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    EngineCore
    EngineMath
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    EngineCore
    EngineMath
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "assimp-vc142-mtd"
        ">"
        "$<$<CONFIG:Release>:"
            "assimp-vc142-mt"
        ">"
        "glfw3"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "assimp-vc142-mtd"
        ">"
        "$<$<CONFIG:Release>:"
            "assimp-vc142-mt"
        ">"
        "glfw3"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

