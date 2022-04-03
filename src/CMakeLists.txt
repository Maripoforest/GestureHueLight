cmake_minimum_required(VERSION 3.16)

project(Hue)

# include_directories(../lib/mlx90640-library/headers)
include_directories(./mlx90640)
include_directories(./hue)
include_directories(.)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)
set(MYMLXLIB ../lib/mlx90640-library/functions)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

add_executable(Hue 
		hue/hue.cpp 
		hue/newuser.cpp 
		hue/fileop.cpp)
target_link_libraries(Hue PRIVATE cpr)	

add_executable(event
<<<<<<< HEAD
		mlx90640/event.cpp
		mywidget.cpp 
		mlx90640/mlx90640_driver.cpp) 
=======
		mywidget.cpp 
<<<<<<< HEAD
		${MYMLXLIB}/mlx90640_driver.cpp
		event.cpp) 


target_link_libraries(Hue PRIVATE cpr)
=======
		mlx90640_driver.cpp) 
>>>>>>> threads
>>>>>>> main

target_link_libraries(event Qt5::Widgets)
target_link_libraries(event Qt5::Gui)
target_link_libraries(event qwt-qt5)




