cmake_minimum_required(VERSION 3.15)

add_executable(LiyStdApp "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_link_libraries(LiyStdApp PRIVATE $<TARGET_OBJECTS:liy_common_sources> "${LIY_COMMON_INCLUDES}")

target_include_directories(LiyStdApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_sources(LiyStdApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

liy_set_compile_options(LiyStdApp)

install(TARGETS LiyStdApp DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin")

liy_message_add_target(LiyStdApp EXE "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
