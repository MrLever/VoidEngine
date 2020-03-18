################################################################################
# Set Files
################################################################################
set(Engine_Modules_Test_Suite
    "Physics/ColliderComponent_test.cpp"
    "Input/InputDefinition_test.cpp"
    "Input/InputManager_test.cpp"
    "Input/ActionBinding_test.cpp"
    "Gameplay/Entity_test.cpp"
    "Gameplay/Transform_test.cpp"
    "EventSystem/EventBus_test.cpp"
    "Window/Window_test.cpp"
)

################################################################################
# Create executable
################################################################################
add_executable(
    EngineCoreTestSuite
    ${Engine_Modules_Test_Suite}
) 

################################################################################
# Link GTest and Engine Modules
################################################################################
target_link_libraries(EngineCoreTestSuite gtest_main EngineCore EngineUtils)

################################################################################
# Link EngineCore Wholearchive to allow access to factory symbols
################################################################################
target_link_options(EngineCoreTestSuite PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineCored>")
target_link_options(EngineCoreTestSuite PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineCore>")