/*
Arthor Xiangmin XU(Wardenfreude)
A Hue static IP and static user on/off brightness control method.
Relies on library cpr https://github.com/libcpr/cpr.git, cpr has some C++ HTTPS method that can be used to send message to the Hue light bulb api.
*/

#include <cpr/cpr.h>
#include <iostream>

void get_user(void) {
	// you should physically press the hue button before using this method
	cpr::Url user{"http://192.168.0.101/api"};
	cpr::Body user_request{"{\"devicetype\":\"Raspberrypi\"}"};
	cpr::Response userid = cpr::Post(user, user_request);
	std::cout << userid.text << std::endl;
	//id printed in terminal, modify the main func with your id.
}

int main(int argc, char** argv) {
	//using get_user method to get your own user.
	//you should know your Hue bridge ip before everything.
	cpr::Url url{"http://192.168.0.101/api/S7BnUlaWvwAs6dZgYErkLO8GAWdRHTdTGi1wxwL0/lights/1/state"};
	int judge = std::stoi(argv[1]);
	std::cout << judge << std::endl;
	
	
	if (judge == 0){
		cpr::Body body1{"{\"on\": false}"};  		// JSON text string
		cpr::Response r1 = cpr::Put(url, body1);                  
		std::cout << r1.text<< std::endl;
	}
	else if (judge == 1) {
		cpr::Body body2{"{\"on\": true, \"bri\":50}"};
		cpr::Response r2 = cpr::Put(url, body2);              
		std::cout << r2.text << std::endl;
	}

    return 0;
}
