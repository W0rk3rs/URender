target_include_directories("URender" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories("URender" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/vendor")
target_include_directories("URender" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/tests")

target_include_directories("URender" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/res")

add_subdirectory("src")
