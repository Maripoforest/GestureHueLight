cmake_minimum_required(VERSION 3.12)
project(Hue)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory("submodule")
add_executable(Hue 
    src/HueOnandOFF.cpp 
  	)
