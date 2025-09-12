cmake_minimum_required(VERSION 3.25)

###打印当前版本
message("[project] Now cmake version is " ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
###限制版本范围
if(${CMAKE_VERSION} VERSION_LESS 3.25)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

#项目描述
project(
    LiyStd
    VERSION 0.0.1
    DESCRIPTION "My std try."
    LANGUAGES CXX
)

set(LIYSTD_LICENSE "LGPL-3.0" CACHE STRING "Library license type")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
# 彩色输出
set(CMAKE_COLOR_DIAGNOSTICS ON)

#接口库,包含所有头文件
set(liy_lib_includes 
    "${PROJECT_SOURCE_DIR}/lib/include/LiyStdArrays"
    "${PROJECT_SOURCE_DIR}/lib/include/LiyStdGraphs"
    "${PROJECT_SOURCE_DIR}/lib/include/LiyStdSets"
    "${PROJECT_SOURCE_DIR}/lib/include"
)
#对象库，包含库的所有源文件
set(liy_lib_sources 
    "${PROJECT_SOURCE_DIR}/lib/src/LiyStdArrays/ArrayList.cpp"
        "${PROJECT_SOURCE_DIR}/lib/src/liyUtil.cpp"
)
#liy_arrays静态连接库的所有源文件
set(liy_arrays_sources
        "${PROJECT_SOURCE_DIR}/lib/src/LiyStdArrays/ArrayList.cpp"
)
add_library(liy_common_includes INTERFACE)  #接口库

add_library(liy_common_sources OBJECT ${liy_lib_sources})   #对象库

#liy_common_includes：库所有头文件
#liy_common_sources: 库所有源文件
target_include_directories(liy_common_includes INTERFACE ${liy_lib_includes})
target_include_directories(liy_common_sources PRIVATE ${liy_lib_includes})

set(LIY_COMMON_INCLUDES liy_common_includes)
set(LIY_COMMON_SOURCES liy_common_sources)

# 定义宏来设置编译选项
macro(liy_set_compile_options TARGET)
    if(MSVC)
        target_compile_options(${TARGET} PRIVATE
            "/Zc:__cplusplus"
            "/permissive-"
            "/utf-8"
            "/wd4819"
        )
    else()
        target_compile_options(${TARGET} PRIVATE
            "-finput-charset=UTF-8" 
            "-fexec-charset=UTF-8"
        )
    endif()
endmacro()

#手动添加子模块
add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(examples/LinearLists)
add_subdirectory(examples/Graphs)
add_subdirectory(examples/Sets)
add_subdirectory(examples/Trees)

set(
    LIY_MSVC_COMPILE_OPTIONS
    "/Zc:__cplusplus"
    "/permissive-"
    "/utf-8"
    "/wd4819"
)

set(
    LIY_GUN_COMPILE_OPTIONS
    "-finput-charset=UTF-8" 
    "-fexec-charset=UTF-8"
)

liy_set_compile_options(liy_common_sources)

# 测试支持
enable_testing()

# 导入Doctest
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
message("[project] add libraries: doctest.")
FetchContent_MakeAvailable(doctest)
message("[project] doctest is available.")

option(BUILD_TESTS "All tests." ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
    message("[project] All tests is now loaded.")
endif()

# 测试开关

