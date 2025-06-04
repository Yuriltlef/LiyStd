cmake_minimum_required(VERSION 3.15)

add_executable(LiyStdApp ${PROJECT_SOURCE_DIR}/app/main.cpp)

target_include_directories(LiyStdApp PRIVATE ${PROJECT_SOURCE_DIR}/lib/include/LiyStdArrays
                                             ${PROJECT_SOURCE_DIR}/lib/include/LiyStdGraphs
                                             ${PROJECT_SOURCE_DIR}/lib/include/LiyStdSets
                                             ${PROJECT_SOURCE_DIR}/app/include
)

target_sources(LiyStdApp PRIVATE ${PROJECT_SOURCE_DIR}/lib/src/LiyStdArrays
                                 ${PROJECT_SOURCE_DIR}/lib/src/LiyStdGraphs
                                 ${PROJECT_SOURCE_DIR}/lib/src/LiyStdSets
                                 ${PROJECT_SOURCE_DIR}/app/src
)
set(Var)
get_property(Var TARGET LiyStdApp PROPERTY CXX_STANDARD)

message("CXX standard of target LiyStdApp is ${Var}")

install(TARGETS LiyStdApp DESTINATION ${PROJECT_SOURCE_DIR}/app/bin)
