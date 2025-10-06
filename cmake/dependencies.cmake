# ---------------------------------------------------------------------------
# function: add_lib60870
#
# Purpose: Minimal wrapping of the original ExternalProject_Add configuration
#          to download, configure, and build lib60870 exactly as in your
#          original snippet—no generalization or parameterization.
#
# Signature:
#   add_lib60870()
#
# Notes:
#   - Relies on these externally defined variables (must be set before calling):
#       LIB60870_NAME
#       PREFIX_PATH
#       CMAKE_C_COMPILER
#       CMAKE_CXX_COMPILER
#       CMAKE_C_FLAGS
#       CMAKE_CXX_FLAGS
#       CMAKE_BUILD_TYPE
#       GIT_EXECUTABLE (if not set, the function will attempt find_package(Git))
#   - Adds an extra step to clone mbedtls v3.6.4 into the dependencies directory
#     of the lib60870 source (as per your original logic), forcing the step each
#     configure by using ALWAYS 1.
#   - Install prefix is fixed to: ${PREFIX_PATH}/install/lib60870
#
# Example Usage:
#   add_lib60870()
# ---------------------------------------------------------------------------
function(add_lib60870)
    include(ExternalProject)

    if(NOT GIT_EXECUTABLE)
        find_package(Git REQUIRED)
    endif()

    set(LIB60870_NAME lib60870)

    ExternalProject_Add(${LIB60870_NAME}
            GIT_REPOSITORY https://github.com/mz-automation/lib60870.git
            GIT_TAG master
            PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib60870
            SOURCE_SUBDIR lib60870-C
            CMAKE_ARGS
            -DCMAKE_POLICY_VERSION_MINIMUM=3.10
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
            -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DBUILD_EXAMPLES:BOOL=OFF
            -DBUILD_TESTS:BOOL=OFF
            -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}/install/lib60870
    )

    ExternalProject_Add_Step(${LIB60870_NAME} clone_mbedtls_3_6
            COMMAND ${GIT_EXECUTABLE} clone --branch v3.6.4 --depth 1 --single-branch https://github.com/Mbed-TLS/mbedtls.git mbedtls-3.6
            WORKING_DIRECTORY <SOURCE_DIR>/lib60870-C/dependencies
            COMMENT "Cloning mbedtls 3.6 for lib60870"
            DEPENDEES download
            DEPENDERS configure
            # ALWAYS 1
    )
endfunction()
