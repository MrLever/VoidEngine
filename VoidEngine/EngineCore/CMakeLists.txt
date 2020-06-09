################################################################################
# Define project: EngineCore
################################################################################
project(EngineCore CXX)

################################################################################
# Set VoidEngine source directories
################################################################################
set(engine_core_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(engine_core_header_dir "${engine_core_include_dir}/core/")
set(engine_core_source_dir "src/")

################################################################################
# Collect header files 
################################################################################
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/core/*.h")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/core/" PREFIX "Header Files" FILES ${CORE_HEADERS})

################################################################################
# Collect Source files 
################################################################################
file(GLOB_RECURSE CORE_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${CORE_SOURCE})

set(Dependencies
    "../../Dependencies/GLAD/src/glad.c"
)
source_group("Dependencies" FILES ${Dependencies})
set_source_files_properties(${Dependencies} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

################################################################################
# Collect all files
################################################################################
set(ALL_FILES
    ${Dependencies}
    ${CORE_HEADERS}
    ${CORE_SOURCE}
)

################################################################################
# Define Static Library Target
################################################################################
add_library(EngineCore STATIC ${ALL_FILES})

################################################################################
# Set target include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE ${VoidEngine_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${VoidEngine_SOURCE_DIR}/Dependencies)
target_include_directories(${PROJECT_NAME} PUBLIC ${VoidEngine_SOURCE_DIR}/Dependencies/GLAD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${VoidEngine_SOURCE_DIR}/Dependencies/GLFW/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${VoidEngine_SOURCE_DIR}/Dependencies/assimp/include)

################################################################################
# Link Dependencies
################################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC EngineUtils)
target_link_libraries(${PROJECT_NAME} PUBLIC EngineMath)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)

################################################################################
# Set Compile Options
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE -DVE_ENABLE_ASSERTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${engine_core_header_dir}VoidEnginePCH.h)

################################################################################
# Set link options
################################################################################
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineUtilsd>")
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineUtils>")

################################################################################
# Set target include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE ${engine_core_include_dir}/core/)
target_include_directories(${PROJECT_NAME} PUBLIC ${engine_utils_include_dir}/)
target_include_directories(${PROJECT_NAME} PUBLIC ${engine_core_include_dir}/)