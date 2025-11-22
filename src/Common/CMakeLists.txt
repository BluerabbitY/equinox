target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Inc
)

target_sources(${PROJECT_NAME}
        PRIVATE
        Log/Log.cpp
)
