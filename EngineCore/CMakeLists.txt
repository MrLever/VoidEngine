################################################################################
# Define module project: EngineCore
################################################################################
project(EngineCore C CXX)

################################################################################
# Set Source groups
################################################################################
set(Dependencies
    "../Dependencies/GLAD/src/glad.c"
)
source_group("Dependencies" FILES ${Dependencies})

set(Header_Files__Engine_Core
    "Game.h"
    "Window.h"
)
source_group("Header Files\\Engine Core" FILES ${Header_Files__Engine_Core})

set(Header_Files__Engine_Core__Audio_System
    "AudioManager.h"
)
source_group("Header Files\\Engine Core\\Audio System" FILES ${Header_Files__Engine_Core__Audio_System})

set(Header_Files__Engine_Core__Event_System
    "EventBus.h"
    "EventBusNode.h"
    "EventDispatcher.h"
)
source_group("Header Files\\Engine Core\\Event System" FILES ${Header_Files__Engine_Core__Event_System})

set(Header_Files__Engine_Core__Event_System__Events
    "AxisInputEvent.h"
    "Event.h"
    "GamepadButtonEvent.h"
    "InputActionEvent.h"
    "KeyboardButtonEvent.h"
    "MouseButtonEvent.h"
    "MouseMovedEvent.h"
    "PauseGameEvent.h"
    "WindowClosedEvent.h"
    "WindowResizedEvent.h"
)
source_group("Header Files\\Engine Core\\Event System\\Events" FILES ${Header_Files__Engine_Core__Event_System__Events})

set(Header_Files__Engine_Core__Input_System
    "AxisInput.h"
    "ControlLayout.h"
    "InputAxis.h"
    "InputManager.h"
)
source_group("Header Files\\Engine Core\\Input System" FILES ${Header_Files__Engine_Core__Input_System})

set(Header_Files__Engine_Core__Input_System__Actions
    "AxisInputAction.h"
    "InputAction.h"
)
source_group("Header Files\\Engine Core\\Input System\\Actions" FILES ${Header_Files__Engine_Core__Input_System__Actions})

set(Header_Files__Engine_Core__Input_System__Input_Definitions
    "GamepadInput.h"
    "Input.h"
    "KeyboardInput.h"
    "MouseInput.h"
)
source_group("Header Files\\Engine Core\\Input System\\Input Definitions" FILES ${Header_Files__Engine_Core__Input_System__Input_Definitions})

set(Header_Files__Engine_Core__Physics_System
    "Manifold.h"
    "PhysicsEngine.h"
)
source_group("Header Files\\Engine Core\\Physics System" FILES ${Header_Files__Engine_Core__Physics_System})

set(Header_Files__Engine_Core__Physics_System__Colliders
    "AABBCollider.h"
    "Collider.h"
    "SphereCollider.h"
)
source_group("Header Files\\Engine Core\\Physics System\\Colliders" FILES ${Header_Files__Engine_Core__Physics_System__Colliders})

set(Header_Files__Engine_Core__Physics_System__Components
    "ColliderComponent.h"
)
source_group("Header Files\\Engine Core\\Physics System\\Components" FILES ${Header_Files__Engine_Core__Physics_System__Components})

set(Header_Files__Engine_Core__Rendering_System
    "Renderer.h"
    "ShaderProgram.h"
)
source_group("Header Files\\Engine Core\\Rendering System" FILES ${Header_Files__Engine_Core__Rendering_System})

set(Header_Files__Engine_Core__Rendering_System__Model_Loading
    "Mesh.h"
    "Vertex.h"
)
source_group("Header Files\\Engine Core\\Rendering System\\Model Loading" FILES ${Header_Files__Engine_Core__Rendering_System__Model_Loading})

set(Header_Files__Engine_Core__Rendering_System__Resources
    "Model.h"
    "Shader.h"
    "Texture.h"
)
source_group("Header Files\\Engine Core\\Rendering System\\Resources" FILES ${Header_Files__Engine_Core__Rendering_System__Resources})

set(Header_Files__Gameplay_Framework
    "Level.h"
)
source_group("Header Files\\Gameplay Framework" FILES ${Header_Files__Gameplay_Framework})

set(Header_Files__Gameplay_Framework__Entity_System__Components
    "CameraComponent.h"
    "Component.h"
    "GraphicsComponent.h"
    "InputComponent.h"
    "PhysicsComponent.h"
)
source_group("Header Files\\Gameplay Framework\\Entity System\\Components" FILES ${Header_Files__Gameplay_Framework__Entity_System__Components})

set(Header_Files__Gameplay_Framework__Entity_System__Entities
    "DefaultPlayerEntity.h"
    "Entity.h"
    "EntityData.h"
    "FloatingFPSPlayer.h"
    "PlayerEntity.h"
    "Projectile.h"
    "StaticObserver.h"
)
source_group("Header Files\\Gameplay Framework\\Entity System\\Entities" FILES ${Header_Files__Gameplay_Framework__Entity_System__Entities})

set(Source_Files__Engine_Core
    "Game.cpp"
    "Window.cpp"
)
source_group("Source Files\\Engine Core" FILES ${Source_Files__Engine_Core})

set(Source_Files__Engine_Core__Audio_System
    "AudioManager.cpp"
)
source_group("Source Files\\Engine Core\\Audio System" FILES ${Source_Files__Engine_Core__Audio_System})

set(Source_Files__Engine_Core__Event_System
    "EventBus.cpp"
    "EventBusNode.cpp"
    "EventDispatcher.cpp"
)
source_group("Source Files\\Engine Core\\Event System" FILES ${Source_Files__Engine_Core__Event_System})

set(Source_Files__Engine_Core__Event_System__Events
    "AxisInputEvent.cpp"
    "Event.cpp"
    "GamepadButtonEvent.cpp"
    "InputActionEvent.cpp"
    "KeyboardButtonEvent.cpp"
    "MouseButtonEvent.cpp"
    "MouseMovedEvent.cpp"
    "PauseGameEvent.cpp"
    "WindowClosedEvent.cpp"
    "WindowResizedEvent.cpp"
)
source_group("Source Files\\Engine Core\\Event System\\Events" FILES ${Source_Files__Engine_Core__Event_System__Events})

set(Source_Files__Engine_Core__Input_System
    "ControlLayout.cpp"
    "InputAxis.cpp"
    "InputManager.cpp"
)
source_group("Source Files\\Engine Core\\Input System" FILES ${Source_Files__Engine_Core__Input_System})

set(Source_Files__Engine_Core__Input_System__Actions
    "AxisInputAction.cpp"
    "InputAction.cpp"
)
source_group("Source Files\\Engine Core\\Input System\\Actions" FILES ${Source_Files__Engine_Core__Input_System__Actions})

set(Source_Files__Engine_Core__Input_System__Input_Definitions
    "AxisInput.cpp"
)
source_group("Source Files\\Engine Core\\Input System\\Input Definitions" FILES ${Source_Files__Engine_Core__Input_System__Input_Definitions})

set(Source_Files__Engine_Core__Physics_System
    "Manifold.cpp"
    "PhysicsEngine.cpp"
)
source_group("Source Files\\Engine Core\\Physics System" FILES ${Source_Files__Engine_Core__Physics_System})

set(Source_Files__Engine_Core__Physics_System__Colliders
    "AABBCollider.cpp"
    "Collider.cpp"
    "SphereCollider.cpp"
)
source_group("Source Files\\Engine Core\\Physics System\\Colliders" FILES ${Source_Files__Engine_Core__Physics_System__Colliders})

set(Source_Files__Engine_Core__Physics_System__Components
    "ColliderComponent.cpp"
)
source_group("Source Files\\Engine Core\\Physics System\\Components" FILES ${Source_Files__Engine_Core__Physics_System__Components})

set(Source_Files__Engine_Core__Rendering_System
    "Renderer.cpp"
    "ShaderProgram.cpp"
)
source_group("Source Files\\Engine Core\\Rendering System" FILES ${Source_Files__Engine_Core__Rendering_System})

set(Source_Files__Engine_Core__Rendering_System__Model_Loading
    "Mesh.cpp"
)
source_group("Source Files\\Engine Core\\Rendering System\\Model Loading" FILES ${Source_Files__Engine_Core__Rendering_System__Model_Loading})

set(Source_Files__Engine_Core__Rendering_System__Resources
    "Model.cpp"
    "Shader.cpp"
    "Texture.cpp"
)
source_group("Source Files\\Engine Core\\Rendering System\\Resources" FILES ${Source_Files__Engine_Core__Rendering_System__Resources})

set(Source_Files__Gameplay_Framework
    "Level.cpp"
)
source_group("Source Files\\Gameplay Framework" FILES ${Source_Files__Gameplay_Framework})

set(Source_Files__Gameplay_Framework__Entity_System__Components
    "CameraComponent.cpp"
    "Component.cpp"
    "GraphicsComponent.cpp"
    "InputComponent.cpp"
    "PhysicsComponent.cpp"
)
source_group("Source Files\\Gameplay Framework\\Entity System\\Components" FILES ${Source_Files__Gameplay_Framework__Entity_System__Components})

set(Source_Files__Gameplay_Framework__Entity_System__Entities
    "DefaultPlayerEntity.cpp"
    "Entity.cpp"
    "EntityData.cpp"
    "FloatingFPSPlayer.cpp"
    "PlayerEntity.cpp"
    "Projectile.cpp"
    "StaticObserver.cpp"
)
source_group("Source Files\\Gameplay Framework\\Entity System\\Entities" FILES ${Source_Files__Gameplay_Framework__Entity_System__Entities})

set(ALL_FILES
    ${Dependencies}
    ${Header_Files__Engine_Core}
    ${Header_Files__Engine_Core__Audio_System}
    ${Header_Files__Engine_Core__Event_System}
    ${Header_Files__Engine_Core__Event_System__Events}
    ${Header_Files__Engine_Core__Input_System}
    ${Header_Files__Engine_Core__Input_System__Actions}
    ${Header_Files__Engine_Core__Input_System__Input_Definitions}
    ${Header_Files__Engine_Core__Physics_System}
    ${Header_Files__Engine_Core__Physics_System__Colliders}
    ${Header_Files__Engine_Core__Physics_System__Components}
    ${Header_Files__Engine_Core__Rendering_System}
    ${Header_Files__Engine_Core__Rendering_System__Model_Loading}
    ${Header_Files__Engine_Core__Rendering_System__Resources}
    ${Header_Files__Gameplay_Framework}
    ${Header_Files__Gameplay_Framework__Entity_System__Components}
    ${Header_Files__Gameplay_Framework__Entity_System__Entities}
    ${Source_Files__Engine_Core}
    ${Source_Files__Engine_Core__Audio_System}
    ${Source_Files__Engine_Core__Event_System}
    ${Source_Files__Engine_Core__Event_System__Events}
    ${Source_Files__Engine_Core__Input_System}
    ${Source_Files__Engine_Core__Input_System__Actions}
    ${Source_Files__Engine_Core__Input_System__Input_Definitions}
    ${Source_Files__Engine_Core__Physics_System}
    ${Source_Files__Engine_Core__Physics_System__Colliders}
    ${Source_Files__Engine_Core__Physics_System__Components}
    ${Source_Files__Engine_Core__Rendering_System}
    ${Source_Files__Engine_Core__Rendering_System__Model_Loading}
    ${Source_Files__Engine_Core__Rendering_System__Resources}
    ${Source_Files__Gameplay_Framework}
    ${Source_Files__Gameplay_Framework__Entity_System__Components}
    ${Source_Files__Gameplay_Framework__Entity_System__Entities}
)

################################################################################
# Specify library properties
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
set(ROOT_NAMESPACE core)

################################################################################
# Set module include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies/GLAD/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/assimp/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

################################################################################
# Link Dependencies
################################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC EngineUtils)
target_link_libraries(${PROJECT_NAME} PUBLIC EngineMath)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)

################################################################################
# Link Utils Wholearchive to allow access to factory symbols
################################################################################
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineUtilsd>")
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineUtils>")