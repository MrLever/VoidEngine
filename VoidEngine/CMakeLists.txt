################################################################################
# Direct EngineModule CMake projects
################################################################################
add_subdirectory(EngineMath)
add_subdirectory(EngineUtils)
add_subdirectory(EngineCore)

### Enable Assertions
target_compile_definitions(EngineCore PRIVATE -DVE_ENABLE_ASSERTS)