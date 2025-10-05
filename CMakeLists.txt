cmake_minimum_required(VERSION 4.0)

project(equinox)

set(CMAKE_CXX_STANDARD 20)

set(PLATFORM "x86_64")

set(PREFIX_PATH "${CMAKE_SOURCE_DIR}/output/${PLATFORM}")

add_subdirectory(src)
