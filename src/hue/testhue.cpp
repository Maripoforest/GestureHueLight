#include "huefunc.h"
#include "newuser.h"

int main() {
    HUEMSG hm;
    std::string msg = "args";
    char rcv[4];
    hm.setURL("https://httpbin.org/get");
    hm.curlGet();
    hm.getResponse();
    int j = 0;
    for (int i = 5;i<9;i++) {
        rcv[j] = hm.gateResponse[i];
        j++;
    }
}