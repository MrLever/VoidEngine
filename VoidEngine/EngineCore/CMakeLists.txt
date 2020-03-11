cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

################################################################################
# Define module project: EngineMath
################################################################################
project(EngineCore CXX)

################################################################################
# Record include directories
################################################################################
set(engine_core_include_dir
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(engine_core_header_dir
  "${engine_core_include_dir}/core/"
)

set(engine_core_source_dir
  "src/"
)

################################################################################
# Collect header files 
################################################################################
### Platform Headers
set(engine_core_platform_core_headers
    "${engine_core_header_dir}/platform/Platform.h"
)
source_group("Header Files\\Platform" FILES ${engine_core_platform_core_headers})

set(engine_core_platform_rendering_headers
    "${engine_core_header_dir}/platform/OpenGL/OpenGLIndexBuffer.h"
    "${engine_core_header_dir}/platform/OpenGL/OpenGLRenderDevice.h"
    "${engine_core_header_dir}/platform/OpenGL/OpenGLVertexArray.h"
    "${engine_core_header_dir}/platform/OpenGL/OpenGLVertexBuffer.h"
)
source_group("Header Files\\Platform\\OpenGL" FILES ${engine_core_platform_rendering_headers})

set(engine_core_platform_windowing_headers
    "${engine_core_header_dir}/platform/windowing/WindowsWindow.h"
)
source_group("Header Files\\Platform\\Windowing" FILES ${engine_core_platform_windowing_headers})

set(engine_core_platform_headers
    ${engine_core_platform_core_headers}
    ${engine_core_platform_rendering_headers}
    ${engine_core_platform_windowing_headers}
)

### Audio Headers
set(engine_core_audio_headers
    "${engine_core_header_dir}/audio/AudioManager.h"
)
source_group("Header Files\\Audio" FILES ${engine_core_audio_headers})

### Event System Headers
set(engine_core_event_system_core_headers
    "${engine_core_header_dir}/event_system/EventBus.h"
    "${engine_core_header_dir}/event_system/EventBusNode.h"
    "${engine_core_header_dir}/event_system/EventDispatcher.h"
)
source_group("Header Files\\Event System" FILES ${engine_core_event_system_core_headers})

set(engine_core_event_system_event_headers
    "${engine_core_header_dir}/event_system/events/AxisInputEvent.h"
    "${engine_core_header_dir}/event_system/events/Event.h"
    "${engine_core_header_dir}/event_system/events/GamepadButtonEvent.h"
    "${engine_core_header_dir}/event_system/events/InputActionEvent.h"
    "${engine_core_header_dir}/event_system/events/KeyboardButtonEvent.h"
    "${engine_core_header_dir}/event_system/events/MouseButtonEvent.h"
    "${engine_core_header_dir}/event_system/events/MouseMovedEvent.h"
    "${engine_core_header_dir}/event_system/events/PauseGameEvent.h"
    "${engine_core_header_dir}/event_system/events/WindowClosedEvent.h"
    "${engine_core_header_dir}/event_system/events/WindowResizedEvent.h"
)
source_group(
    "Header Files\\Event System\\Events" 
    FILES ${engine_core_event_system_event_headers}
)

set(engine_core_event_system_headers
    ${engine_core_event_system_core_headers}
    ${engine_core_event_system_event_headers}
)


### Gameplay Framework Headers
set(engine_core_gameplay_framework_core_headers
    "${engine_core_header_dir}/gameplay_framework/Component.h"
    "${engine_core_header_dir}/gameplay_framework/Entity.h"
    "${engine_core_header_dir}/gameplay_framework/EntityData.h"
)
source_group(
    "Header Files\\Gameplay Framework" 
    FILES ${engine_core_gameplay_framework_core_headers}
)


set(engine_core_gameplay_framework_entity_headers
    "${engine_core_header_dir}/gameplay_framework/entities/Observer.h"
    "${engine_core_header_dir}/gameplay_framework/entities/FloatingFPSPlayer.h"
    "${engine_core_header_dir}/gameplay_framework/entities/PlayerEntity.h"
    "${engine_core_header_dir}/gameplay_framework/entities/Projectile.h"
    "${engine_core_header_dir}/gameplay_framework/entities/StaticObserver.h"
)
source_group(
    "Header Files\\Gameplay Framework\\Entities" 
    FILES ${engine_core_gameplay_framework_entity_headers}
)

set(engine_core_gameplay_framework_headers
    ${engine_core_gameplay_framework_core_headers}
    ${engine_core_gameplay_framework_entity_headers}
)

### Input System
set(engine_core_input_core_headers
    "${engine_core_header_dir}/input/AxisInputAction.h"
    "${engine_core_header_dir}/input/ControlLayout.h"
    "${engine_core_header_dir}/input/InputAction.h"
    "${engine_core_header_dir}/input/InputAxis.h"
    "${engine_core_header_dir}/input/InputManager.h"
)
source_group(
    "Header Files\\Input\\" 
    FILES ${engine_core_input_core_headers}
)

set(engine_core_input_components_headers
    "${engine_core_header_dir}/input/components/InputComponent.h"
)
source_group(
    "Header Files\\Input\\Components" 
    FILES ${engine_core_input_components_headers}
)

set(engine_core_input_definitions_headers
    "${engine_core_header_dir}/input/definitions/AxisInput.h"
    "${engine_core_header_dir}/input/definitions/GamepadInput.h"
    "${engine_core_header_dir}/input/definitions/Input.h"
    "${engine_core_header_dir}/input/definitions/KeyboardInput.h"
    "${engine_core_header_dir}/input/definitions/MouseInput.h"
)
source_group(
    "Header Files\\Input\\Definitions" 
    FILES ${engine_core_input_definitions_headers}
)

set(engine_core_input_headers
    ${engine_core_input_core_headers}
    ${engine_core_input_components_headers}
    ${engine_core_input_definitions_headers}
)

### Physics System
set(engine_core_physics_core_headers
    "${engine_core_header_dir}/physics/Manifold.h"
    "${engine_core_header_dir}/physics/PhysicsEngine.h"
)
source_group(
    "Header Files\\Physics" 
    FILES ${engine_core_physics_core_headers}
)

set(engine_core_physics_colliders_headers
    "${engine_core_header_dir}/physics/colliders/Collider.h"
    "${engine_core_header_dir}/physics/colliders/AABBCollider.h"
    "${engine_core_header_dir}/physics/colliders/SphereCollider.h"
)
source_group(
    "Header Files\\Physics\\Colliders" 
    FILES ${engine_core_physics_colliders_headers}
)

set(engine_core_physics_components_headers
    "${engine_core_header_dir}/physics/components/PhysicsComponent.h"
    "${engine_core_header_dir}/physics/components/ColliderComponent.h"
)
source_group(
    "Header Files\\Physics\\Components" 
    FILES ${engine_core_physics_components_headers}
)

set(engine_core_physics_headers
    ${engine_core_physics_core_headers}
    ${engine_core_physics_colliders_headers}
    ${engine_core_physics_components_headers}
)

## Rendering System
set(engine_core_rendering_core_headers
    "${engine_core_header_dir}/rendering/BufferLayout.h"
    "${engine_core_header_dir}/rendering/IndexBuffer.h"
    "${engine_core_header_dir}/rendering/LightingEnvironment.h"
    "${engine_core_header_dir}/rendering/Mesh.h"
    "${engine_core_header_dir}/rendering/Model.h"
    "${engine_core_header_dir}/rendering/RenderCommand.h"
    "${engine_core_header_dir}/rendering/RenderDevice.h"
    "${engine_core_header_dir}/rendering/Renderer.h"
    "${engine_core_header_dir}/rendering/Shader.h"
    "${engine_core_header_dir}/rendering/ShaderProgram.h"
    "${engine_core_header_dir}/rendering/Texture.h"
    "${engine_core_header_dir}/rendering/Vertex.h"
    "${engine_core_header_dir}/rendering/VertexArray.h"
    "${engine_core_header_dir}/rendering/VertexBuffer.h"
    "${engine_core_header_dir}/rendering/Viewport.h"
)
source_group(
    "Header Files\\Rendering" 
    FILES ${engine_core_rendering_core_headers}
)

set(engine_core_rendering_component_headers
    "${engine_core_header_dir}/rendering/components/CameraComponent.h"
    "${engine_core_header_dir}/rendering/components/GraphicsComponent.h"
)
source_group(
    "Header Files\\Rendering\\Components" 
    FILES ${engine_core_rendering_component_headers}
)

set(engine_core_rendering_component_light_headers
    "${engine_core_header_dir}/rendering/components/lights/DirectionalLightComponent.h"
    "${engine_core_header_dir}/rendering/components/lights/PointLightComponent.h"
)
source_group(
    "Header Files\\Rendering\\Components\\Lights" 
    FILES ${engine_core_rendering_component_light_headers}
)


set(engine_core_rendering_headers
    ${engine_core_rendering_core_headers}
    ${engine_core_rendering_component_headers}
    ${engine_core_rendering_component_light_headers}
)

### Collect all headers
set(engine_core_headers
    "${engine_core_platform_headers}"
    "${engine_core_audio_headers}"
    "${engine_core_event_system_headers}"
    "${engine_core_gameplay_framework_headers}"
    "${engine_core_input_headers}"
    "${engine_core_physics_headers}"
    "${engine_core_rendering_headers}"
    "${engine_core_header_dir}/Game.h"
    "${engine_core_header_dir}/Level.h"
    "${engine_core_header_dir}/Window.h"
    "${engine_core_header_dir}/Scene.h"
    "${engine_core_header_dir}/SceneLoader.h"
)

################################################################################
# Collect source files 
################################################################################
### Platform Headers
set(engine_core_platform_core_source
    "src/platform/Platform.cpp"
)
source_group("Source Files\\Platform" FILES ${engine_core_platform_core_source})

set(engine_core_platform_rendering_source
    "src/platform/OpenGL/OpenGLIndexBuffer.cpp"
    "src/platform/OpenGL/OpenGLRenderDevice.cpp"
    "src/platform/OpenGL/OpenGLVertexArray.cpp"
    "src/platform/OpenGL/OpenGLVertexBuffer.cpp"
)
source_group("Source Files\\Platform\\OpenGL" FILES ${engine_core_platform_rendering_source})

set(engine_core_platform_windowing_source
    "src/platform/windowing/WindowsWindow.cpp"
)
source_group("Source Files\\Platform\\Windowing" FILES ${engine_core_platform_windowing_source})

set(engine_core_platform_source
    ${engine_core_platform_core_source}
    ${engine_core_platform_rendering_source}
    ${engine_core_platform_windowing_source}
)

### Audio Sources
set(engine_core_audio_source
    "${engine_core_source_dir}/audio/AudioManager.cpp"
)
source_group("Source Files\\Audio" FILES ${engine_core_audio_source})

### Event System Sources
set(engine_core_event_system_core_source
    "${engine_core_source_dir}/event_system/EventBus.cpp"
    "${engine_core_source_dir}/event_system/EventBusNode.cpp"
    "${engine_core_source_dir}/event_system/EventDispatcher.cpp"
)
source_group("Source Files\\Event System" FILES ${engine_core_event_system_core_source})

set(engine_core_event_system_event_source
    "${engine_core_source_dir}/event_system/events/AxisInputEvent.cpp"
    "${engine_core_source_dir}/event_system/events/Event.cpp"
    "${engine_core_source_dir}/event_system/events/GamepadButtonEvent.cpp"
    "${engine_core_source_dir}/event_system/events/InputActionEvent.cpp"
    "${engine_core_source_dir}/event_system/events/KeyboardButtonEvent.cpp"
    "${engine_core_source_dir}/event_system/events/MouseButtonEvent.cpp"
    "${engine_core_source_dir}/event_system/events/MouseMovedEvent.cpp"
    "${engine_core_source_dir}/event_system/events/PauseGameEvent.cpp"
    "${engine_core_source_dir}/event_system/events/WindowClosedEvent.cpp"
    "${engine_core_source_dir}/event_system/events/WindowResizedEvent.cpp"
)
source_group(
    "Source Files\\Event System\\Events" 
    FILES ${engine_core_event_system_event_source}
)

set(engine_core_event_system_source
    ${engine_core_event_system_core_source}
    ${engine_core_event_system_event_source}
)


### Gameplay Framework Sources
set(engine_core_gameplay_framework_core_source
    "${engine_core_source_dir}/gameplay_framework/Component.cpp"
    "${engine_core_source_dir}/gameplay_framework/Entity.cpp"
    "${engine_core_source_dir}/gameplay_framework/EntityData.cpp"
)
source_group(
    "Source Files\\Gameplay Framework" 
    FILES ${engine_core_gameplay_framework_core_source}
)


set(engine_core_gameplay_framework_entity_source
    "${engine_core_source_dir}/gameplay_framework/entities/Observer.cpp"
    "${engine_core_source_dir}/gameplay_framework/entities/FloatingFPSPlayer.cpp"
    "${engine_core_source_dir}/gameplay_framework/entities/PlayerEntity.cpp"
    "${engine_core_source_dir}/gameplay_framework/entities/Projectile.cpp"
    "${engine_core_source_dir}/gameplay_framework/entities/StaticObserver.cpp"
)
source_group(
    "Source Files\\Gameplay Framework\\Entities" 
    FILES ${engine_core_gameplay_framework_entity_source}
)

set(engine_core_gameplay_framework_source
    ${engine_core_gameplay_framework_core_source}
    ${engine_core_gameplay_framework_entity_source}
)

### Input System
set(engine_core_input_core_source
    "${engine_core_source_dir}/input/AxisInputAction.cpp"
    "${engine_core_source_dir}/input/ControlLayout.cpp"
    "${engine_core_source_dir}/input/InputAction.cpp"
    "${engine_core_source_dir}/input/InputAxis.cpp"
    "${engine_core_source_dir}/input/InputManager.cpp"
)
source_group(
    "Source Files\\Input\\" 
    FILES ${engine_core_input_core_source}
)

set(engine_core_input_components_source
    "${engine_core_source_dir}/input/components/InputComponent.cpp"
)
source_group(
    "Source Files\\Input\\Components" 
    FILES ${engine_core_input_components_source}
)

set(engine_core_input_definitions_source
    "${engine_core_source_dir}/input/definitions/AxisInput.cpp"
)
source_group(
    "Source Files\\Input\\Definitions" 
    FILES ${engine_core_input_definitions_source}
)

set(engine_core_input_source
    ${engine_core_input_core_source}
    ${engine_core_input_components_source}
    ${engine_core_input_definitions_source}
)

### Physics System
set(engine_core_physics_core_source
    "${engine_core_source_dir}/physics/Manifold.cpp"
    "${engine_core_source_dir}/physics/PhysicsEngine.cpp"
)
source_group(
    "Source Files\\Physics" 
    FILES ${engine_core_physics_core_source}
)

set(engine_core_physics_colliders_source
    "${engine_core_source_dir}/physics/colliders/Collider.cpp"
    "${engine_core_source_dir}/physics/colliders/AABBCollider.cpp"
    "${engine_core_source_dir}/physics/colliders/SphereCollider.cpp"
)
source_group(
    "Source Files\\Physics\\Colliders" 
    FILES ${engine_core_physics_colliders_source}
)

set(engine_core_physics_components_source
    "${engine_core_source_dir}/physics/components/PhysicsComponent.cpp"
    "${engine_core_source_dir}/physics/components/ColliderComponent.cpp"
)
source_group(
    "Source Files\\Physics\\Components" 
    FILES ${engine_core_physics_components_source}
)

set(engine_core_physics_source
    ${engine_core_physics_core_source}
    ${engine_core_physics_colliders_source}
    ${engine_core_physics_components_source}
)

## Rendering System
set(engine_core_rendering_core_source
    "${engine_core_source_dir}/rendering/BufferLayout.cpp"
    "${engine_core_source_dir}/rendering/IndexBuffer.cpp"
    "${engine_core_source_dir}/rendering/Mesh.cpp"
    "${engine_core_source_dir}/rendering/Model.cpp"
    "${engine_core_source_dir}/rendering/RenderCommand.cpp"
    "${engine_core_source_dir}/rendering/RenderDevice.cpp"
    "${engine_core_source_dir}/rendering/Renderer.cpp"
    "${engine_core_source_dir}/rendering/Shader.cpp"
    "${engine_core_source_dir}/rendering/ShaderProgram.cpp"
    "${engine_core_source_dir}/rendering/Texture.cpp"
    "${engine_core_source_dir}/rendering/VertexArray.cpp"
    "${engine_core_source_dir}/rendering/VertexBuffer.cpp"
)
source_group(
    "Source Files\\Rendering" 
    FILES ${engine_core_rendering_core_source}
)

set(engine_core_rendering_component_source
    "${engine_core_source_dir}/rendering/components/CameraComponent.cpp"
    "${engine_core_source_dir}/rendering/components/GraphicsComponent.cpp"
)
source_group(
    "Source Files\\Rendering\\Components" 
    FILES ${engine_core_rendering_component_source}
)

set(engine_core_rendering_component_light_source
    "${engine_core_source_dir}/rendering/components/lights/DirectionalLightComponent.cpp"
    "${engine_core_source_dir}/rendering/components/lights/PointLightComponent.cpp"
)
source_group(
    "Source Files\\Rendering\\Components\\Lights" 
    FILES ${engine_core_rendering_component_light_source}
)


set(engine_core_rendering_source
    ${engine_core_rendering_core_source}
    ${engine_core_rendering_component_source}
    ${engine_core_rendering_component_light_source}
)

### Collect all source
set(engine_core_source
    "${engine_core_platform_source}"
    "${engine_core_audio_source}"
    "${engine_core_event_system_source}"
    "${engine_core_gameplay_framework_source}"
    "${engine_core_input_source}"
    "${engine_core_physics_source}"
    "${engine_core_rendering_source}"
    "${engine_core_source_dir}/Game.cpp"
    "${engine_core_source_dir}/Level.cpp"
    "${engine_core_source_dir}/Window.cpp"
    "${engine_core_source_dir}/Scene.cpp"
    "${engine_core_source_dir}/SceneLoader.cpp"
)

set(Dependencies
    "../../Dependencies/GLAD/src/glad.c"
)
source_group("Dependencies" FILES ${Dependencies})

################################################################################
# Build Static Library
################################################################################
set(ALL_FILES
    ${Dependencies}
    ${engine_core_headers}
    ${engine_core_source}
)

add_library(EngineCore STATIC ${ALL_FILES})

################################################################################
# Link Dependencies
################################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC EngineUtils)
target_link_libraries(${PROJECT_NAME} PUBLIC EngineMath)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)

################################################################################
# Set link options
################################################################################
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineUtilsd>")
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineUtils>")

################################################################################
# Set module include directories
################################################################################
target_include_directories(EngineCore PRIVATE ${engine_core_include_dir}/core/)
target_include_directories(EngineCore PUBLIC ${engine_utils_include_dir}/)
target_include_directories(EngineCore PUBLIC ${engine_core_include_dir}/)

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