cmake_minimum_required(VERSION 3.15)

add_executable(arrayListExample "${CMAKE_CURRENT_SOURCE_DIR}/arrayListExample.cpp")

target_link_libraries(arrayListExample PRIVATE "${LIY_COMMON_INCLUDES}")