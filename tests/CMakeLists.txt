cmake_minimum_required(VERSION 3.25)

# 添加所有模块
add_subdirectory(Arrays)
add_subdirectory(Graphs)
add_subdirectory(Sets)

# 添加集成测试
add_executable(
    integretion_tests
    "${CMAKE_CURRENT_SOURCE_DIR}/integrationTests.cpp"
    )

target_link_libraries(
    integretion_tests
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

# 兼容指令
liy_set_compile_options(integretion_tests)

liy_set_color_output(integretion_tests)

liy_message_add_target(integretion_tests EXE "${CMAKE_CURRENT_SOURCE_DIR}/integrationTests.cpp")

liy_message_add_test_target(integrationTests integretion_tests)

liy_message_color_output("integrationTests")  

add_test(NAME integrationTests COMMAND integretion_tests)
 