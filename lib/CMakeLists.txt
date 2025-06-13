cmake_minimum_required(VERSION 3.15)

add_library(liy_arrays STATIC
        "${liy_arrays_sources}"
)

target_include_directories(liy_arrays PRIVATE
    "${liy_lib_includes}"
)

set_target_properties(
    liy_arrays PROPERTIES
    OUTPUT_NAME "arrays"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/bin"
)