# Arthor: Xiangmin XU (Maripoforest) Haiyang You
# CMake file for the project

cmake_minimum_required(VERSION 3.16)

project(Hue)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CURL_LIBRARY "-lcurl")

find_package(CURL REQUIRED)

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
include_directories(./mlx90640)
include_directories(./hue)
# include_directories(.)

add_executable(Hue 
		main_hue.cpp
		hue/newuser.cpp 
		hue/fileop.cpp
		hue/huefunc.cpp)
target_link_libraries(Hue ${CURL_LIBRARIES})

add_executable(main
		hue/newuser.cpp
		hue/fileop.cpp
		hue/huefunc.cpp
		main.cpp
		mywidget.cpp 
		mlx90640/mlx90640_driver.cpp) 

target_link_libraries(main ${CURL_LIBRARIES})
target_link_libraries(main Qt5::Widgets)
target_link_libraries(main Qt5::Gui)
target_link_libraries(main qwt-qt5)

add_executable(testd	
		hue/fileop.cpp
		hue/huefunc.cpp
		hue/newuser.cpp
		testm.cpp
		mywidget.cpp
		mlx90640/mlx90640_driver.cpp) 

target_link_libraries(testd ${CURL_LIBRARIES})
target_link_libraries(testd Qt5::Widgets)
target_link_libraries(testd Qt5::Gui)
target_link_libraries(testd qwt-qt5)