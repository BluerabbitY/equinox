cmake_minimum_required(VERSION 4.0)

project(equinox)

if (NOT CMAKE_PREFIX_PATH)
    message(FATAL_ERROR "CMAKE_PREFIX_PATH is not set.")
else ()
    message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
endif()

set(CMAKE_CXX_STANDARD 20)

set(PLATFORM "x86_64")

set(PREFIX_PATH "${CMAKE_SOURCE_DIR}/output/${PLATFORM}")

add_subdirectory(src)
