#define BOOST_TEST_MODULE MAXtests
#include <boost/test/unit_test.hpp>
#include "ansiprint.h"

BOOST_AUTO_TEST_CASE(ANSIT){
    float pixel[768] = {0};
    pixel[0] = -100;
    int error = ansi_print(pixel);
    BOOST_CHECK_EQUAL(error, 1);

    pixel[0] = 1000;
    error = ansi_print(pixel);
    BOOST_CHECK_EQUAL(error, 1);

}
