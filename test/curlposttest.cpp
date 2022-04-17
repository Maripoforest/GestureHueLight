#define BOOST_TEST_MODULE MAXtests
#include <boost/test/unit_test.hpp>
#include "hue/huefunc.h"

BOOST_AUTO_TEST_CASE(POSTT){
    HUEMSG hm;
    std::string msg = "thisistest";
    char rcv[10];
    hm.setURL("https://httpbin.org/post");
    hm.setMessage("thisistest");
    hm.curlPost();
    hm.getResponse();
    int j = 0;
    for (int i = 28;i<38;i++) {
        rcv[j] = hm.gateResponse[i];
        j++;
    }
    BOOST_CHECK_EQUAL(strcmp(rcv, msg.c_str()), 0);

}
