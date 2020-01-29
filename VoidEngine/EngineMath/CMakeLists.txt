cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

################################################################################
# Define module project: EngineMath
################################################################################
project(EngineMath CXX)

################################################################################
# Acquire source files
################################################################################
set(engine_math_include_dir
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(engine_math_header_dir
  "${engine_math_include_dir}/math"
)

set(Header_Files
    "${engine_math_header_dir}/MathConstants.h"
    "${engine_math_header_dir}/Quaternion.h"
    "${engine_math_header_dir}/Rotator.h"
    "${engine_math_header_dir}/Vector.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "src/Quaternion.cpp"
    "src/Rotator.cpp"
    "src/Vector.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Specify build as Static Library
################################################################################
add_library(EngineMath STATIC ${ALL_FILES})

################################################################################
# Set Module Include Directory
################################################################################
target_include_directories(EngineMath PUBLIC ${engine_math_include_dir}/)

