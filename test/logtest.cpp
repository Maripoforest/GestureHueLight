#define BOOST_TEST_MODULE MAXtests
#include <boost/test/unit_test.hpp>
#include "hue/fileop.h"

BOOST_AUTO_TEST_CASE(LOGT){
    logfile lf;
    std::vector<std::string> lines;
    BOOST_CHECK_EQUAL(lf.readfile(lines), 1);

}
