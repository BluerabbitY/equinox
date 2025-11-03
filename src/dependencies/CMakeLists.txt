include_directories("${CMAKE_CURRENT_LIST_DIR}/install/include")

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/install/include")
target_link_directories(${PROJECT_NAME}  PRIVATE "${CMAKE_CURRENT_LIST_DIR}/install/lib")
target_link_libraries(${PROJECT_NAME} PRIVATE lib60870)
