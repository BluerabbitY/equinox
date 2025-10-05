include(${CMAKE_SOURCE_DIR}/cmake/build.cmake)

message(STATUS "Project name: ${CMAKE_PROJECT_NAME}")

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

add_dependencies(${CMAKE_PROJECT_NAME} lib60870)

set_target_output_dir(${CMAKE_PROJECT_NAME} ${PREFIX_PATH} EXE)
