include(${CMAKE_SOURCE_DIR}/cmake/build.cmake)

add_subdirectory(dependencies)

option(BUILD_HUSKARUI_STATIC_LIBRARY "HuskarUI is static library." OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_policy(SET QTP0001 NEW)

#qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(${PROJECT_NAME}
        main/main.cpp
)

add_dependencies(${CMAKE_PROJECT_NAME} lib60870)
add_dependencies(${CMAKE_PROJECT_NAME} HuskarUI)

message(STATUS "QML module name: ${PROJECT_NAME}")

qt_add_qml_module(${PROJECT_NAME}
        URI ${PROJECT_NAME}
        VERSION 1.0
        QML_FILES
            qml/main.qml
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<BOOL:${BUILD_HUSKARUI_STATIC_LIBRARY}>:BUILD_HUSKARUI_STATIC_LIBRARY>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PREFIX_PATH}/include/HuskarUI)
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PREFIX_PATH}/lib)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        Qt6::Quick
        HuskarUIBasic
        $<$<BOOL:${BUILD_HUSKARUI_STATIC_LIBRARY}>:HuskarUIBasicPlugin>
)

set(WIN_RC_FILE "")
if(WIN32)
    include(${CMAKE_SOURCE_DIR}/src/dependencies/HuskarUI/src/HuskarUI/.cmake/HuskarUIHelper.cmake)
    string(TIMESTAMP CURRENT_YEAR "%Y")
    set(WIN_RC_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_Resource.rc)
    hus_add_win_rc(${PROJECT_NAME}
            COMMENTS "Equinox"
            NAME "${PROJECT_NAME}.exe"
            COMPANY "BluerRbbit studio"
            DESCRIPTION "Tool for IEC60870-5-101/104 protocol"
            VERSION "${PROJECT_VERSION}"
            COPYRIGHT "Copyright (C) ${CURRENT_YEAR} mengps. All rights reserved."
            ICONS resources/icon.ico
            OUTPUT_FILE "${WIN_RC_FILE}"
    )
endif()

set_target_output_dir(${CMAKE_PROJECT_NAME} ${PREFIX_PATH} EXE)
