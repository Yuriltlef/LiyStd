cmake_minimum_required(VERSION 3.15)

add_executable(LiyStdApp "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_link_libraries(LiyStdApp PRIVATE $<TARGET_OBJECTS:liy_common_sources> "${LIY_COMMON_INCLUDES}")

target_include_directories(LiyStdApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_sources(LiyStdApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (MSVC)
	target_compile_options(LiyStdApp PRIVATE 
				"/Zc:__cplusplus"
				"/permissive-"
                "/utf-8"
				"/wd4819"
	)
else() 
	target_compile_options(LiyStdApp PRIVATE "-finput-charset=UTF-8" "-fexec-charset=UTF-8")
endif()


set(Var)
get_property(Var TARGET LiyStdApp PROPERTY CXX_STANDARD)

message("CXX standard of target LiyStdApp is ${Var}")

install(TARGETS LiyStdApp DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin")
