cmake_minimum_required(VERSION 3.13)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
link_libraries(/home/pi/cpr/build/lib/libcpr.so)
include_directories(/home/pi/cpr/include)
#link your own libcpr.so file and cpr include above

add_executable(Hue HueOnandOFF.cpp)
