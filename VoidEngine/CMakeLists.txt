################################################################################
# Define project
################################################################################
project(VoidEngine C CXX)

################################################################################
# Include Void Engine sub-modules
################################################################################
add_subdirectory(EngineMath)
add_subdirectory(EngineUtils)
add_subdirectory(EngineCore)
add_subdirectory(Tests)

################################################################################
# Enable Assertions
################################################################################
target_compile_definitions(EngineCore PRIVATE -DVE_ENABLE_ASSERTS)

################################################################################
# Define Void engine library that is linked to by game project
################################################################################
add_library(${PROJECT_NAME} STATIC "src/main.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine/)

################################################################################
# Link VoidEngine to EngineCore
################################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC EngineCore)
target_link_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:/WHOLEARCHIVE:EngineCored>")
target_link_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:/WHOLEARCHIVE:EngineCore>")

################################################################################
# Define Asset installation rules
################################################################################
add_custom_target(InstallAssets ALL 
    COMMAND ${CMAKE_COMMAND} -E echo "RUNNING ASSET INSTALL COMMANDS:"
)
set_target_properties(InstallAssets PROPERTIES FOLDER Engine/Tools)

# Install game assets and configurations to executable directory
# If building standalone there won't be a game directory to copy to.
if(NOT ${VoidEngine_Build_Standalone})
    # Copy Defualt Assets
    add_custom_command(TARGET InstallAssets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Installing Required Assets to ${GAME_PROJECT_NAME}/Assets/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Default
            $<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>/Assets/Default
    )

    add_custom_command(TARGET InstallAssets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Installing ${GAME_PROJECT_NAME} Assets to ${GAME_PROJECT_NAME}/Assets/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${GAME_ASSETS_DIRECTORY}
            $<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>/Assets/
    )

    add_custom_command(TARGET InstallAssets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Installing Void Engine default config files to ${GAME_PROJECT_NAME}/Config/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/Config/
            $<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>/Config/
    )

    add_custom_command(TARGET InstallAssets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Installing ${GAME_PROJECT_NAME} config files to ${GAME_PROJECT_NAME}/Config/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${GAME_CONFIG_DIRECTORY}
            $<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>/Config/
    )
endif()

################################################################################
# Set working directory for MSVC generators
################################################################################
if(MSVC)
    set_property(TARGET ${GAME_PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>")
endif()

if(VoidEngine_Enable_Sample_Project)
    # Add custom command to InstallAssets to copy resources to sample project
endif()