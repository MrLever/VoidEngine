cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

################################################################################
# Define module project: EngineMath
################################################################################
project(EngineCore CXX)

################################################################################
# Acquire source files
################################################################################
set(engine_core_include_dir
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(engine_core_header_dir
  "${engine_core_include_dir}/core/"
)

set(ALL_FILES
    ""
)

################################################################################
# Specify build as Static Library
################################################################################
add_library(EngineCore STATIC ${ALL_FILES})

################################################################################
# Set Module Include Directory
################################################################################
target_include_directories(EngineCore PUBLIC ${engine_core_include_dir}/)
target_include_directories(EngineCore PUBLIC ${engine_core_include_dir}/)
