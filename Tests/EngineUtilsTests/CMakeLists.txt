################################################################################
# Set Files
################################################################################
set(Engine_Utils_Test_Suite
    "Configurable_test.cpp"
    "Configuration_test.cpp"
    "Name_test.cpp"
    "Table_test.cpp"
    "Factory_test.cpp"
    "ResourceManager_test.cpp"
    "ThreadPool_test"
    "ThreadSafeQueue_test.cpp"
    "GenericUtilities_test.cpp"
    "RTTI_test.cpp"
)

################################################################################
# Create executable
################################################################################
add_executable(
    EngineUtilsTestSuite
    ${Engine_Utils_Test_Suite}
) 

################################################################################
# Link GTest and Engine Modules
################################################################################
target_link_libraries(EngineUtilsTestSuite gtest_main EngineUtils VoidEngine)

################################################################################
# Link EngineCore Wholearchive to allow access to factory symbols
################################################################################
target_link_options(EngineUtilsTestSuite PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:VoidEngined>")
target_link_options(EngineUtilsTestSuite PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:VoidEngine>")