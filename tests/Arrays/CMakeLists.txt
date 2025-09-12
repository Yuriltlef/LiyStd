cmake_minimum_required(VERSION 3.25)

# 添加集成测试
add_executable(
    arraryListClass_test
    "${CMAKE_CURRENT_SOURCE_DIR}/ArrayList_all_tests.cpp"
    )
message(
    "[project] add executable: arraryListClass_test. src: " 
    "${CMAKE_CURRENT_SOURCE_DIR}/ArrayList_all_tests.cpp"
    )

target_link_libraries(
    arraryListClass_test
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

if (MSVC)
	target_compile_options(arraryListClass_test PRIVATE 
				${LIY_MSVC_COMPILE_OPTIONS}
	)
else() 
	target_compile_options(arraryListClass_test PRIVATE 
				${LIY_GUN_COMPILE_OPTIONS}
	)
endif()

message(
    "[project] add test: arraryListClassTest. src: arraryListClass_test" 
    )   
#--------------------------------------------------------------------------
# 添加集成测试 linkedListClassTest
add_executable(
    linkedListClass_test
    "${CMAKE_CURRENT_SOURCE_DIR}/LinkedList_all_tests.cpp"
    )
message(
    "[project] add executable: linkedListClass_test. src: " 
    "${CMAKE_CURRENT_SOURCE_DIR}/LinkedList_all_tests.cpp"
    )

target_link_libraries(
    linkedListClass_test
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

if (MSVC)
	target_compile_options(linkedListClass_test PRIVATE 
				${LIY_MSVC_COMPILE_OPTIONS}
	)
else() 
	target_compile_options(linkedListClass_test PRIVATE 
				${LIY_GUN_COMPILE_OPTIONS}
	)
endif()

message(
    "[project] add test: linkedListClassTest. src: linkedListClass_test" 
    )   
#--------------------------------------------------------------------------
# 添加集成测试 arraysAllClassTest
add_executable(
    arrayAllClass_test
    "${CMAKE_CURRENT_SOURCE_DIR}/Arrays_all_tests.cpp"
    )
message(
    "[project] add executable: arrayAllClass_test. src: " 
    "${CMAKE_CURRENT_SOURCE_DIR}/Arrays_all_tests.cpp"
    )

target_link_libraries(
    arrayAllClass_test
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

if (MSVC)
	target_compile_options(arrayAllClass_test PRIVATE 
				${LIY_MSVC_COMPILE_OPTIONS}
	)
else() 
	target_compile_options(arrayAllClass_test PRIVATE 
				${LIY_GUN_COMPILE_OPTIONS}
	)
endif()

message(
    "[project] add test: arraysAllClassTest. src: arrayAllClass_test" 
    )   
#################################################################
add_test(NAME arraryListClassTest COMMAND arraryListClass_test)
#---------------------------------------------------------------
add_test(NAME linkedListClassTest COMMAND linkedListClass_test)
#---------------------------------------------------------------
add_test(NAME arraysAllClassTest COMMAND linkedListClass_test)
#################################################################