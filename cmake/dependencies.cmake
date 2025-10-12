function(fetch_dependencies target repo branch dependencyList preMakerVar)

    if (NOT GIT_EXECUTABLE)
        find_package(Git REQUIRED)
    endif ()

    if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/${target}/.git")
        add_custom_command(
                OUTPUT "${target}/.git"
                DEPENDS ${${preMakerVar}}
                COMMAND ${CMAKE_COMMAND} -E make_directory "${target}"
                COMMAND ${GIT_EXECUTABLE} clone --branch ${branch} --single-branch ${repo} "${target}"
                COMMAND ${GIT_EXECUTABLE} -C "${target}" submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                COMMENT "Cloning dependencies ${target} branch ${branch}"
        )

        set(dependencyListLocal "${${dependencyList}}")
        list(APPEND dependencyListLocal "${target}/.git")
        set(${dependencyList} "${dependencyListLocal}" PARENT_SCOPE)

        set(${preMakerVar} "${target}/.git" PARENT_SCOPE)
    else ()
        message(STATUS "Dependency ${target} already exists and is not empty, skipping.")
    endif ()
endfunction()
