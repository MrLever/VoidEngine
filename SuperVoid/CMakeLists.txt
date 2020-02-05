project(SuperVoid CXX)

################################################################################
# Set Files
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
# Create Executable
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})
set(ROOT_NAMESPACE SuperVoid)

################################################################################
# Add Include Directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies)

################################################################################
# Link Dependencies (Wholearchive to allow access to factory symbols)
################################################################################
target_link_libraries(${PROJECT_NAME} EngineCore)
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineCored>")
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineCore>")

################################################################################
# Copy resource files
################################################################################
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources/
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Settings/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/Settings/
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources/ ${PROJECT_BINARY_DIR}/Resources/
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Settings/ ${PROJECT_BINARY_DIR}/Settings/
)