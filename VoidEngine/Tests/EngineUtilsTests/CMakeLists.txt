################################################################################
# Collect tests
################################################################################
file(GLOB_RECURSE TEST_SOURCE CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE TEST_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

################################################################################
# Create executable
################################################################################
add_executable(
    EngineUtilsTestSuite
    ${TEST_SOURCE}
    ${TEST_HEADERS}
) 

set_target_properties(EngineUtilsTestSuite PROPERTIES FOLDER Engine/Tests/)

################################################################################
# Link GTest and Engine Modules
################################################################################
target_link_libraries(EngineUtilsTestSuite gtest_main EngineUtils EngineCore)

################################################################################
# Link EngineCore Wholearchive to allow access to factory symbols
################################################################################
target_link_options(EngineUtilsTestSuite PRIVATE "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineCored>")
target_link_options(EngineUtilsTestSuite PRIVATE "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineCore>")