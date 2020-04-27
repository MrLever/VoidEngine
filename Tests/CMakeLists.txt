################################################################################
# Add test suites
################################################################################
add_subdirectory(EngineMathTests)
add_subdirectory(EngineUtilsTests)
add_subdirectory(EngineCoreTests)

################################################################################
# Set solution folders
################################################################################
set_target_properties(MathTestSuite PROPERTIES FOLDER Tests/)
set_target_properties(EngineUtilsTestSuite PROPERTIES FOLDER Tests/)
set_target_properties(EngineCoreTestSuite PROPERTIES FOLDER Tests/)