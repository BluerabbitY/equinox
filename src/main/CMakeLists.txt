include(${CMAKE_SOURCE_DIR}/cmake/build.cmake)

message(STATUS "Project name: ${CMAKE_PROJECT_NAME}")

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

set_target_output_dir(${CMAKE_PROJECT_NAME} ${PREFIX_PATH} EXE)
