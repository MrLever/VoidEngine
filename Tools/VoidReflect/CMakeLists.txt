################################################################################
# Define project: EngineCore
################################################################################
project(VoidReflect CXX)


################################################################################
# Collect header files 
################################################################################
file(GLOB_RECURSE VoidReflect_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source/" PREFIX "Header Files" FILES ${CORE_HEADERS})

################################################################################
# Collect Source files 
################################################################################
file(GLOB_RECURSE VoidReflect_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" PREFIX "Source Files" FILES ${CORE_SOURCE})

set(ALL_FILES
    ${VoidReflect_HEADERS}
    ${VoidReflect_SOURCE}
)

add_executable(${PROJECT_NAME} ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine/Tools)