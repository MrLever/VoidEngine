cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(EngineMath CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Acquire source files
set(Header_Files
    "MathConstants.h"
    "Quaternion.h"
    "Rotator.h"
    "Vector.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Quaternion.cpp"
    "Rotator.cpp"
    "Vector.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

# Add Math files to static library
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

