#define BOOST_TEST_MODULE MAXtests
#include <boost/test/unit_test.hpp>
#include "hue/huefunc.h"

BOOST_AUTO_TEST_CASE(GETT){
    HUEMSG hm;
    std::string msg = "thisistest";
    char rcv[10];
    hm.setURL("https://httpbin.org/put");
    hm.setMessage("thisistest");
    hm.curlPut();
    hm.getResponse();
    int j = 0;
    for (int i =51;i<61;i++) {
        rcv[j] = hm.gateResponse[i];
        j++;
    }
    BOOST_CHECK_EQUAL(strcmp(rcv, msg.c_str()), 0);


}
