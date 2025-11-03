cmake_minimum_required(VERSION 4.0)

set(HERALD_CMAKE_CONFIG_FILE_PATH "${CMAKE_SOURCE_DIR}/.cache/herald.config")
if(EXISTS "${HERALD_CMAKE_CONFIG_FILE_PATH}")
    file(READ "${HERALD_CMAKE_CONFIG_FILE_PATH}" CMAKE_PREFIX_PATH)
else()
    message(FATAL_ERROR "Please run command \"HeraldTool.py --setup\" to initialize project first")
endif()

if (NOT CMAKE_PREFIX_PATH)
    message(FATAL_ERROR "CMAKE_PREFIX_PATH is not set.")
else ()
    message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
endif ()

set(HERALD_VERSION "0.0.1.0")
project(herald VERSION ${HERALD_VERSION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "Target CPU: ${CMAKE_SYSTEM_PROCESSOR}")
set(PREFIX_PATH "${CMAKE_SOURCE_DIR}/output/${CMAKE_SYSTEM_PROCESSOR}")

add_subdirectory(src)
