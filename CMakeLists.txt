cmake_minimum_required(VERSION 3.18.2)

project("Root_URender" VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB  "SRC" CONFIGURE_DEPENDS "renderer/src/*.h"
			"renderer/src/*.cpp" 
			"renderer/src/tests/*.cpp"
			"renderer/src/tests/*.h"
			"renderer/src/vendor/imgui/*.cpp"
			"renderer/src/vendor/imgui/*.h"
			"renderer/src/vendor/stb_image/*.cpp"
			"renderer/src/vendor/stb_image/*.h"
			"Dependencies/GLEW/include/GL/*.h"
			"Dependencies/GLFW/include/GLFW/*.h"
			)

add_executable("URender" "${SRC}")

add_subdirectory("Renderer")
add_subdirectory("Dependencies")

add_definitions(-D GLEW_STATIC)


#find and link OpenGL: REQUIRED!!!
find_package(OpenGL REQUIRED)
target_link_libraries("URender" PRIVATE "${OPENGL_LIBRARIES}")

set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT "URender")


