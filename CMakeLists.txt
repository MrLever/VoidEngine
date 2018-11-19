cmake_minimum_required (VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SUPPRESS_REGENERATION true)

project (Project-Coati)

file(GLOB Source
	"Source/*.h"
	"Source/*.cpp"
)

add_executable(Project-Coati ${Source})


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Project-Coati)