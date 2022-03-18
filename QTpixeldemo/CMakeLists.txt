cmake_minimum_required(VERSION 3.0.0)
project(demo05)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets  Gui REQUIRED)

add_executable(demo05
  mywidget.cpp
  main.cpp
)

target_link_libraries(demo05 Qt5::Widgets)
target_link_libraries(demo05 Qt5::Gui)


install(TARGETS demo05)

