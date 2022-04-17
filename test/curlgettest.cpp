#define BOOST_TEST_MODULE MAXtests
#include <boost/test/unit_test.hpp>
#include "hue/huefunc.h"

BOOST_AUTO_TEST_CASE(GETT){
    HUEMSG hm;
    std::string msg = "args";
    std::string rcv = "1234";
    hm.setURL("https://httpbin.org/get");
    hm.curlGet();
    hm.getResponse();
    int j = 0;
    for (int i = 5;i<9;i++) {
        rcv[j] = hm.gateResponse[i];
        j++;
    }


    BOOST_CHECK_EQUAL(strcmp(rcv.c_str(), msg.c_str()), 0);

}
