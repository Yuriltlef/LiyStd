cmake_minimum_required(VERSION 3.25)

add_executable(arrayListExample "${CMAKE_CURRENT_SOURCE_DIR}/arrayListExample.cpp")
message("[project] add executable: arrayListExample. src: " ${LIY_COMMON_SOURCES})

liy_set_compile_options(arrayListExample)

# 链接到对象库和接口库
target_link_libraries(
	arrayListExample PRIVATE 
	$<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
	)