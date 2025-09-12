cmake_minimum_required(VERSION 3.25)

add_executable(arrayListExample "${CMAKE_CURRENT_SOURCE_DIR}/arrayListExample.cpp")
message("[project] add executable: arrayListExample. src: " ${LIY_COMMON_SOURCES})

if (MSVC)
	target_compile_options(arrayListExample PRIVATE 
				${LIY_MSVC_COMPILE_OPTIONS}
	)
else() 
	target_compile_options(arrayListExample PRIVATE 
				${LIY_GUN_COMPILE_OPTIONS}
	)
endif()

# 链接到对象库和接口库
target_link_libraries(
	arrayListExample PRIVATE 
	$<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
	)