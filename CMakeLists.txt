cmake_minimum_required(VERSION 3.15)

###打印当前版本
message("Now cmake version is " ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
###限制版本范围
if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

#项目描述
project(
    LiyStd
    VERSION 0.0.1
    DESCRIPTION "My std try."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(app)
