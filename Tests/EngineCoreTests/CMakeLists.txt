################################################################################
# Set Files
################################################################################
set(Engine_Utils_Test_Suite
    "Utils/Name_test.cpp"
    "Utils/Table_test.cpp"
    "Utils/Factory_test.cpp"
    "Utils/ResourceManager_test.cpp"
    "Utils/ThreadPool_test"
    "Utils/ThreadSafeQueue_test.cpp"
)

################################################################################
# Create executable
################################################################################
add_executable(
    EngineCoreTestSuite
    ${Engine_Utils_Test_Suite}
) 

################################################################################
# Link GTest and Engine Modules
################################################################################
target_link_libraries(EngineCoreTestSuite gtest_main EngineCore)

################################################################################
# Link EngineCore Wholearchive to allow access to factory symbols
################################################################################
target_link_options(EngineCoreTestSuite PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineCored>")
target_link_options(EngineCoreTestSuite PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineCore>")