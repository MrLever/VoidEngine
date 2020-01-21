project(SuperVoid CXX)

### Collect and organize files
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

### Set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies/GLAD/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/assimp/include)

################################################################################
# Dependencies
################################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC EngineMath)
target_link_libraries(${PROJECT_NAME} PUBLIC EngineCore)