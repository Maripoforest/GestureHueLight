cmake_minimum_required(VERSION 3.16)

project(Hue)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

add_executable(Hue main.cpp newuser.cpp fileop.cpp)

# this project has dependencies on cpr and curl libs.
# if you have make installed cpr locally, use the following instead of fetch content.

# local use
# link_libraries(/usr/local/lib/libcpr.so)
# include_directories(/usr/local/include)

# fetch remotely
# include(FetchContent)
# FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
#                        GIT_TAG beb9e98806bb84bcc130a2cebfbcbbc6ce62b335) #1.7.2
# FetchContent_MakeAvailable(cpr)

target_link_libraries(Hue PRIVATE cpr)
