cmake_minimum_required(VERSION 3.16)

project(Hue)

include_directories(../lib/mlx90640-library/headers)
include_directories(.)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)
set(MYMLXLIB ../lib/mlx90640-library/functions)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

add_executable(Hue 
		main.cpp 
		newuser.cpp 
		fileop.cpp)
target_link_libraries(Hue PRIVATE cpr)	

#add_executable(sensor
#		main2.cpp 
#		${MYMLXLIB}/MLX90640_API.cpp 
#		${MYMLXLIB}/MLX90640_I2C_Driver.cpp
#		mywidget.cpp
#		ansiprint.cpp) 
#target_link_libraries(sensor event Qt5::Widgets)
#target_link_libraries(sensor event Qt5::Gui)
#target_link_libraries(sensor event qwt-qt5)

add_executable(event
		event.cpp
		mywidget.cpp 
		${MYMLXLIB}/mlx90640_driver.cpp) 

target_link_libraries(event Qt5::Widgets)
target_link_libraries(event Qt5::Gui)
target_link_libraries(event qwt-qt5)


# install(TARGETS sensor)


