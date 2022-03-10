cmake_minimum_required(VERSION 3.12)
project(Hue)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/submodule)

add_subdirectory("submodule")
add_executable(Hue 
    src/main.cpp 
    src/foo.cpp)
