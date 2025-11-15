
find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(SCRIPT ${CMAKE_SOURCE_DIR}/script/HeraldTool.py)

set(QM_OUTPUT_DIR ${PREFIX_PATH})

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(QM_OUTPUT_DIR "${QM_OUTPUT_DIR}/herald.app/Contents/MacOS")
endif()

add_custom_target(Localization ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Update localization files..."
        COMMAND ${Python3_EXECUTABLE} ${SCRIPT} --release-localization ${QM_OUTPUT_DIR}
        DEPENDS ${SCRIPT}
        VERBATIM
)

add_dependencies(${PROJECT_NAME} Localization)
