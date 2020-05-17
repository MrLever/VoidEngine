################################################################################
# Include Void Engine sub-modules
################################################################################
add_subdirectory(EngineMath)
add_subdirectory(EngineUtils)
add_subdirectory(EngineCore)
add_subdirectory(Tests)

################################################################################
# Set Folder Properties
################################################################################
set_target_properties(EngineUtils PROPERTIES FOLDER Engine/)
set_target_properties(EngineMath PROPERTIES FOLDER Engine/)
set_target_properties(EngineCore PROPERTIES FOLDER Engine/)

### Enable Assertions
target_compile_definitions(EngineCore PRIVATE -DVE_ENABLE_ASSERTS)