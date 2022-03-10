/*
Arthor: Xiangmin XU (Maripoforest)
A Hue static IP and static user on/off brightness control method.
Relies on library cpr https://github.com/libcpr/cpr.git, cpr has some C++ HTTPS method that can be used to send message to the Hue light bulb api.
*/

/*
Arthor: Xiangmin XU (Maripoforest)
A Hue static IP and static user on/off brightness control method.
Relies on library cpr https://github.com/libcpr/cpr.git, cpr has some C++ HTTPS method that can be used to send message to the Hue light bulb api.
*/

#include <cpr/cpr.h>
#include <iostream>
#include <string>

void get_user(void) {
	// you should physically press the hue button before using this method
	std::cout << "Please press the physical hue button,\npress Enter to continue." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	cpr::Url user{"http://192.168.0.100/api"};
	cpr::Body user_request{"{\"devicetype\":\"Raspberrypi\"}"};
	cpr::Response userid = cpr::Post(user, user_request);
	std::cout << userid.text << std::endl;
	//id printed in terminal, modify the main func with your id.
}

int main(int argc, char** argv) {
	//using get_user method to get your own user.
	//you should know your Hue bridge ip before everything.
	std::string api = "http://192.168.0.100/api/S7BnUlaWvwAs6dZgYErkLO8GAWdRHTdTGi1wxwL0/lights/1/state";
	int judge = -1;
	std::string order = argv[1];
	if(order == "new") {
		std::cout << "get user\n";
		get_user();
	}
	else if(order == "user") {
		if (argc == 4) {
			std::string user = argv[2];
			api = "http://192.168.0.100/api/" + user + "/lights/1/state";
			judge = std::stoi(argv[3]);
		}
		else {
			std::cout << "No user input! Please paste the <user> in the double quote after get_user()" << std::endl;
		}
		
	}
	else if(order != "new" && order != "user") {
		judge = std::stoi(argv[1]);
		//std::cout << judge << std::endl;
	}

	cpr::Url url{api};

	if (judge == 0){
		cpr::Body body1{"{\"on\": false}"};  		// JSON text string
		cpr::Response r1 = cpr::Put(url, body1);                  
		std::cout << r1.text<< std::endl;
	}
	else if (judge > 0) {
		std::string msg = "{\"on\": true, \"bri\":"+ order +"}";
		cpr::Body body2{msg};
		cpr::Response r2 = cpr::Put(url, body2);              
		std::cout << r2.text << std::endl;
	}

    return 0;
}
