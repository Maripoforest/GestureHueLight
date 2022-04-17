find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (../src
                     ${Boost_INCLUDE_DIRS})

add_definitions (-DBOOST_TEST_DYN_LINK)

find_package(CURL REQUIRED)
set(CURL_LIBRARY "-lcurl")
include_directories(${CURL_INCLUDE_DIR})

add_executable (ANSIT ansitest.cpp)
target_link_libraries (ANSIT
                       ANSIPrintLib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )

add_executable (GETT curlgettest.cpp)
target_link_libraries (GETT
                       HueLib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
target_link_libraries(GETT ${CURL_LIBRARIES})

add_executable (PUTT curlputtest.cpp)
target_link_libraries (PUTT
                       HueLib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
target_link_libraries(PUTT ${CURL_LIBRARIES})

add_executable (POSTT curlposttest.cpp)
target_link_libraries (POSTT
                       HueLib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
target_link_libraries(POSTT ${CURL_LIBRARIES})


add_executable (LOGT logtest.cpp)
target_link_libraries (LOGT
                       HueLib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )

add_executable (NEWT newusertest.cpp)
target_link_libraries (NEWT
                       HueLib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
target_link_libraries(NEWT ${CURL_LIBRARIES})