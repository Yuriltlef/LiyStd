cmake_minimum_required(VERSION 3.15)

add_executable(arrayListExample "${CMAKE_CURRENT_SOURCE_DIR}/arrayListExample.cpp")

if (MSVC)
	target_compile_options(arrayListExample PRIVATE 
				"/Zc:__cplusplus"
				"/permissive-"
	)
endif()

message(${LIY_COMMON_SOURCES})

target_link_libraries(arrayListExample PRIVATE $<TARGET_OBJECTS:liy_common_sources> "${LIY_COMMON_INCLUDES}")