################################################################################
# Define module project: EngineUtils
################################################################################
project(EngineUtils C CXX)

################################################################################
# Set directory shortcuts
################################################################################
set(engine_utils_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(engine_utils_header_dir "${engine_utils_include_dir}/utils/")
set(engine_utils_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/")

################################################################################
# Collect header files 
################################################################################
file(GLOB_RECURSE UTILS_HEADERS CONFIGURE_DEPENDS "${engine_utils_header_dir}/*.h")
source_group(TREE "${engine_utils_header_dir}" PREFIX "Header Files" FILES ${UTILS_HEADERS})

################################################################################
# Collect source files 
################################################################################
file(GLOB_RECURSE UTILS_SOURCE CONFIGURE_DEPENDS "${engine_utils_source_dir}/*.cpp")
source_group(TREE "${engine_utils_source_dir}" PREFIX "Source Files" FILES ${UTILS_SOURCE})

### Combine files into single target
set(ALL_FILES 
    ${UTILS_HEADERS}  
    ${UTILS_SOURCE} 
)

################################################################################
# Specify build as Static Library
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

################################################################################
# Set target include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE ${VoidEngine_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${VoidEngine_SOURCE_DIR}/Dependencies)
target_include_directories(${PROJECT_NAME} PRIVATE ${VoidEngine_SOURCE_DIR}/Dependencies/GLAD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${VoidEngine_SOURCE_DIR}/Dependencies/GLFW/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${VoidEngine_SOURCE_DIR}/Dependencies/assimp/include)

################################################################################
# Set Module Include Directory
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC ${engine_utils_include_dir}/)
target_include_directories(${PROJECT_NAME} PRIVATE ${engine_utils_header_dir}/)
target_include_directories(${PROJECT_NAME} PRIVATE ${engine_utils_OSAL_header_dir}/)