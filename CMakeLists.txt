cmake_minimum_required(VERSION 2.8)
project(GestureHue)

add_subdirectory(src)
add_subdirectory(test)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CURL_LIBRARY "-lcurl")

include_directories(${CURL_INCLUDE_DIR})
include_directories(.src/mlx90640)
include_directories(.src/hue)

find_package(CURL REQUIRED)
find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

enable_testing()

add_library (ANSIPrintLib
                src/ansiprint.cpp
                src/ansiprint.h)

add_library (HueLib
                src/hue/fileop.cpp
                src/hue/fileop.h
                src/hue/huefunc.cpp
                src/hue/huefunc.h
                src/hue/newuser.cpp
                src/hue/newuser.h)

add_library (MLXLib
                src/mlx90640/mlx90640_driver.h
                src/mlx90640/mlx90640_driver.cpp
                src/mywidget.cpp
                src/mywidget.h
                src/hue/fileop.h
                src/hue/fileop.cpp
                src/hue/newuser.cpp
                src/hue/newuser.h
                src/hue/huefunc.cpp
                src/hue/huefunc.h)

target_link_libraries(MLXLib Qt5::Widgets)
target_link_libraries(MLXLib Qt5::Gui)
target_link_libraries(MLXLib qwt-qt5)

add_test(NAME ANSITest COMMAND ANSIT)
add_test(NAME HueGetTest COMMAND GETT)
add_test(NAME HuePutTest COMMAND PUTT)
add_test(NAME HuePostTest COMMAND POSTT)
add_test(NAME HueLogTest COMMAND LOGT)
add_test(NAME HueNewUserRequestTest COMMAND NEWT)
add_test(NAME SensorTest COMMAND SENT)

