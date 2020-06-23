################################################################################
# Set Files
################################################################################
set(Math_Test_Suite 
    "Quaternions_test.cpp"
    "Rotators_test.cpp"
    "Vector_test.cpp"
)

################################################################################
# Create executable
################################################################################
add_executable(
    MathTestSuite
    ${Math_Test_Suite}
)

set_target_properties(MathTestSuite PROPERTIES FOLDER Engine/Tests/)

################################################################################
# Link GTest and Engine Modules
################################################################################
target_link_libraries(MathTestSuite gtest_main EngineMath)