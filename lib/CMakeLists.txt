cmake_minimum_required(VERSION 3.15)

add_library(liy_arrays STATIC
        "${liy_arrays_sources}"
)

target_include_directories(liy_arrays PRIVATE
    "${liy_lib_includes}"
)

if (MSVC)
	target_compile_options(liy_arrays PRIVATE 
				"/Zc:__cplusplus"
				"/permissive-"
                "/utf-8"
				"/wd4819"
	)
else() 
	target_compile_options(liy_arrays PRIVATE "-finput-charset=UTF-8" "-fexec-charset=UTF-8")
endif()


set_target_properties(
    liy_arrays PROPERTIES
    OUTPUT_NAME "arrays"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/bin"
)

