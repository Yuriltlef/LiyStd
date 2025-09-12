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
message(
    "[project] add executable: integretion_tests. src: " 
    "${CMAKE_CURRENT_SOURCE_DIR}/integrationTests.cpp"
    )

target_link_libraries(
    integretion_tests
    doctest
    $<TARGET_OBJECTS:liy_common_sources> 
	"${LIY_COMMON_INCLUDES}"
    )

add_test(NAME integrationTests COMMAND integretion_tests)
message(
    "[project] add test: integrationTests. src: integretion_tests" 
    )   