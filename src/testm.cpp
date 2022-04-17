#include "mlx90640/mlx90640_driver.h"
#include "mywidget.h"
#include "hue/huefunc.h"

int main(int argc, char** argv){

    HUEMSG hm;
    std::string msg = "thisistest";
    std::string rcv = "1234567890";
    hm.setURL("https://httpbin.org/post");
    hm.setMessage("thisistest");
    hm.curlPost();
    hm.getResponse();
    int j = 0;
    for (int i = 28;i<38;i++) {
        rcv[j] = hm.gateResponse[i];
        j++;
    }
    
    std::cout << rcv << msg << std::endl;

    return 0;
}