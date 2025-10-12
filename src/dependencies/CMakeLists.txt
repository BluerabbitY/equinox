include(${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake)

set(allDependency "")
set(prevMarker "")
fetch_dependencies("lib60870" "https://github.com/BluerabbitY/lib60870.git" "master" allDependency prevMarker)
fetch_dependencies("lib60870/lib60870-C/dependencies/mbedtls-3.6" "https://github.com/Mbed-TLS/mbedtls.git" "v3.6.4" allDependency prevMarker)
fetch_dependencies("HuskarUI" "https://github.com/mengps/HuskarUI.git" "master" allDependency prevMarker)
fetch_dependencies("spdlog" "https://github.com/gabime/spdlog.git" "v1.x" allDependency prevMarker)

add_custom_target(fetch_all DEPENDS ${allDependency})

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib60870/lib60870-C)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/HuskarUI)
