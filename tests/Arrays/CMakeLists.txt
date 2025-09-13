cmake_minimum_required(VERSION 3.25)

# 添加集成测试
add_executable(
    arraryListClass_test
    "${CMAKE_CURRENT_SOURCE_DIR}/ArrayList_all_tests.cpp"
    )

target_link_libraries(
    arraryListClass_test
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

liy_set_compile_options(arraryListClass_test)

liy_set_color_output(arraryListClass_test)

liy_message_add_target(arraryListClass_test EXE "${CMAKE_CURRENT_SOURCE_DIR}/ArrayList_all_tests.cpp")

liy_message_add_test_target(arraryListClassTest arraryListClass_test)

liy_message_color_output("arraryListClassTest")  
#--------------------------------------------------------------------------
# 添加集成测试 linkedListClassTest
add_executable(
    linkedListClass_test
    "${CMAKE_CURRENT_SOURCE_DIR}/LinkedList_all_tests.cpp"
    )

target_link_libraries(
    linkedListClass_test
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

liy_set_compile_options(linkedListClass_test)

liy_message_add_target(linkedListClass_test EXE "${CMAKE_CURRENT_SOURCE_DIR}/LinkedList_all_tests.cpp")

liy_message_add_test_target(linkedListClassTest linkedListClass_test)

liy_message_color_output("linkedListClassTest")  
#--------------------------------------------------------------------------
# 添加集成测试 arraysAllClassTest
add_executable(
    arrayAllClass_test
    "${CMAKE_CURRENT_SOURCE_DIR}/Arrays_all_tests.cpp"
    )

target_link_libraries(
    arrayAllClass_test
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

liy_set_compile_options(arrayAllClass_test)

liy_message_add_target(arrayAllClass_test EXE "${CMAKE_CURRENT_SOURCE_DIR}/Arrays_all_tests.cpp")

liy_message_add_test_target(arraysAllClassTest arrayAllClass_test)

liy_message_color_output("arraysAllClassTest")  
#################################################################
add_test(NAME arraryListClassTest COMMAND arraryListClass_test)
#---------------------------------------------------------------
add_test(NAME linkedListClassTest COMMAND linkedListClass_test)
#---------------------------------------------------------------
add_test(NAME arraysAllClassTest COMMAND linkedListClass_test)
#################################################################