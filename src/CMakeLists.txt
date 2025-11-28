include(${CMAKE_SOURCE_DIR}/cmake/build.cmake)

# Make all found packages global to avoid seaching them multiple times
set(CMAKE_FIND_PACKAGE_TARGETS_GLOBAL ON)

find_package(Qt6 6.8.3 EXACT REQUIRED COMPONENTS
        Quick
)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_LIST_DIR}/Dependencies/install")

find_package(HuskarUI REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/Common)

# Make Qt Creator aware of where the QML modules live
list(APPEND QML_IMPORT_PATH "${CMAKE_CURRENT_LIST_DIR}/View")
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "" FORCE)

# Qt build specific options, need to be defined before any Qt target
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY QT_QML_IMPORT_PATH "${QML_IMPORT_PATH}")

include_directories(${CMAKE_CURRENT_LIST_DIR}/common)

capitalize(${PROJECT_NAME} APP_NAME)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CONFIG:Debug>, $<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
        APP_NAME="${APP_NAME}"
        APP_VERSION="${PROJECT_VERSION}"
        SPDLOG_COMPILED_LIB
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        Qt6::Quick
        HuskarUI::Basic
        spdlog::spdlog
        pugixml::pugixml
)

set(WIN_RC_FILE "")
if (WIN32)
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
endif ()

set_target_output_dir(${CMAKE_PROJECT_NAME} ${PREFIX_PATH} EXE)

# add additional sources from subdirectories
add_subdirectory(Dependencies)
add_subdirectory(Localization)
add_subdirectory(Common)
add_subdirectory(Model)
add_subdirectory(View)
add_subdirectory(ViewModel)
add_subdirectory(Herald)
