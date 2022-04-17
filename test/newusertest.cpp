#define BOOST_TEST_MODULE MAXtests
#include <boost/test/unit_test.hpp>
#include "hue/newuser.h"

BOOST_AUTO_TEST_CASE(LOGT){
    newuser nu;
    bool changed;
    char head[3];
    std::string ret = nu.get_ip(changed);
    for(int i=0;i<3;i++) {
        head[i] = ret[i];
    }
    int x = 1;
    if (strcmp(head, "192") == 0 || strcmp(ret.c_str(), "NOBRIDGE") == 0) {
        x = 0;
    }
    BOOST_CHECK_EQUAL(x, 0);
}
