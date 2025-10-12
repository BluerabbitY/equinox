# ---------------------------------------------------------------------------
# function: set_target_output_dir
#
# Purpose:
#   Set the per-target output directory (archive/library, runtime, etc.) for a
#   given project target using a precomputed prefix path, differentiating
#   between library and executable layouts.
#
# Signature:
#   set_target_output_dir(<Target> <PrefixPath> <Mode>)
#
# Parameters:
#   Target
#     - The CMake target name (typically the same as or derived from the project
#       name declared via project()) that has already been created with
#       add_library() or add_executable().
#
#   PrefixPath
#     - A fully prepared base directory (absolute or relative) under which the
#       final output path will be formed.
#     - This argument is assumed to have been validated / normalized by the
#       caller (e.g. no trailing slash issues, already platform-adjusted).
#     - Do NOT append type-specific or configuration-specific segments here;
#       this function derives those as needed.
#
#   Mode
#     - Specifies which artifact class to configure:
#         LIB  -> Configure output directories for a library target
#
#         EXE  -> Configure output directories for an executable target
#
#     - Only one of: LIB, EXE (extend if future use requires more types).
#
# Example Usage:
#   set_target_output_dir(MyLib  "example_path" LIB)
#   set_target_output_dir(MyTool "example_path" EXE)
#
# ---------------------------------------------------------------------------
function(set_target_output_dir Target PrefixPath Mode)
    if (NOT TARGET ${Target})
        message(FATAL_ERROR "Target '${Target}' does not exist.")
    endif ()

    set(MODE_LIST "LIB;EXE")
    list(FIND MODE_LIST "${Mode}" idx)
    if (idx EQUAL -1)
        message(FATAL_ERROR "Invalid output: '${Mode}'，option：${MODE_LIST}")
    endif ()

    if (${Mode} EQUAL LIB)
        set(basePath "${PrefixPath}/lib")
    else ()
        set(basePath "${PrefixPath}")
    endif ()

    set_target_properties(${Target} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${basePath}"
            LIBRARY_OUTPUT_DIRECTORY "${basePath}"
            RUNTIME_OUTPUT_DIRECTORY "${basePath}"
    )

    foreach (buildType Debug Release RelWithDebInfo MinSizeRel)
        string(TOLOWER "${buildType}" lc)
        set_target_properties(${Target} PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY_${buildType} "${basePath}/${lc}"
                LIBRARY_OUTPUT_DIRECTORY_${buildType} "${basePath}/${lc}"
                RUNTIME_OUTPUT_DIRECTORY_${buildType} "${basePath}/${lc}"
        )
    endforeach ()
endfunction()

function(capitalize input output)
    string(SUBSTRING "${input}" 0 1 first)
    string(TOUPPER "${first}" first_upper)
    string(SUBSTRING "${input}" 1 -1 rest)
    set(result "${first_upper}${rest}")
    set(${output} "${result}" PARENT_SCOPE)
endfunction()
