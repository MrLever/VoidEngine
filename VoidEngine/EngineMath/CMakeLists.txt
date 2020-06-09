cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

################################################################################
# Define module project: EngineMath
################################################################################
project(EngineMath CXX)

################################################################################
# Set project structure
################################################################################
set(engine_math_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(engine_math_header_dir "${engine_math_include_dir}/math")
set(engine_math_src_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")

################################################################################
# Collect header files 
################################################################################
file(GLOB_RECURSE MATH_HEADERS CONFIGURE_DEPENDS "${engine_math_header_dir}/*.h")
source_group(TREE "${engine_math_header_dir}" PREFIX "Header Files" FILES ${MATH_HEADERS})

################################################################################
# Collect source files 
################################################################################
file(GLOB_RECURSE MATH_SOURCE CONFIGURE_DEPENDS "${engine_math_src_dir}/*.cpp")
source_group(TREE "${engine_math_src_dir}" PREFIX "Source Files" FILES ${MATH_SOURCE})

set(ALL_FILES
    ${MATH_HEADERS}
    ${MATH_SOURCE}
)

################################################################################
# Specify build as Static Library
################################################################################
add_library(EngineMath STATIC ${ALL_FILES})

################################################################################
# Set Module Include Directory
################################################################################
target_include_directories(EngineMath PUBLIC ${engine_math_include_dir}/)

