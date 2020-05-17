project(SuperVoid CXX)

################################################################################
# Set Files
################################################################################
set(Header_Files_Entities
    "Entities/Asteroid.h"
    "Entities/AsteroidEmitter.h"
    "Entities/BouncingCube.h"
    "Entities/PlayerShip.h"
)
source_group("Header Files\\Entities" FILES ${Header_Files_Entities})

set(Source_Files
    "Core.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files_Entities
    "Entities/Asteroid.cpp"
    "Entities/AsteroidEmitter.cpp"
    "Entities/BouncingCube.cpp"
    "Entities/PlayerShip.cpp"
)
source_group("Source Files\\Entities" FILES ${Source_Files_Entities})

set(Header_Files_Components
    "Components/ShipCamera.h"
)
source_group("Header Files\\Components" FILES ${Header_Files_Components})

set(Source_Files_Components
    "Components/ShipCamera.cpp"
)
source_group("Source Files\\Components" FILES ${Source_Files_Components})

set(ALL_FILES
    ${Header_Files_Entities}
    ${Source_Files_Entities}
    ${Header_Files_Components}
    ${Source_Files_Components}
    ${Source_Files}
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