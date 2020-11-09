target_link_libraries("URender" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/GLFW/lib-vc2017/glfw3.lib")

target_link_libraries("URender" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/GLEW/lib/Release/Win32/glew32s.lib")

target_include_directories("URender" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include")
target_include_directories("URender" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GLEW/include")
