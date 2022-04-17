find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (../src
                     ${Boost_INCLUDE_DIRS})

add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (ANSIT ansitest.cpp)
target_link_libraries (ANSIT
                       ANSIPrintLib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
