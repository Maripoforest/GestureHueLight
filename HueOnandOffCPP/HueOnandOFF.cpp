/*
Arthor: Xiangmin XU (Maripoforest)
A Hue static IP and static user on/off brightness control method.
Relies on library cpr https://github.com/libcpr/cpr.git, cpr has some C++ HTTPS method that can be used to send message to the Hue light bulb api.
*/

#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int get_brightness(std::string str) {

	int judge = -1;
	try {
		judge = std::stoi(str);
		if (judge < 0 || judge > 255) {
			judge = -1;
			throw (judge);
		}
	}catch(...) {
		std::cerr << "No valid brightness input, please input integer between 0-255.\n";
	}
	return judge;

}

std::string get_user(void) {
	// you should physically press the hue button while using this method

	std::cout << "Please press the physical hue button,\npress Enter to continue." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

	cpr::Url user{"http://192.168.0.100/api"};
	cpr::Body user_request{"{\"devicetype\":\"Raspberrypi\"}"};

	cpr::Response userid = cpr::Post(user, user_request);
	std::cout << userid.text << std::endl;
	//id printed in terminal, modify the main func with your id.
	std::string username = userid.text.substr(25, 40);
	return username;
}

int main(int argc, char** argv) {
	
	//get the static ip and username
	std::string filename("../log.txt");

	std::ifstream input_file(filename);
	std::vector<std::string> lines;
    std::string line;

	bool ip_changed = false;
	bool user_changed = false;

    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << filename << "'" << std::endl;
        return EXIT_FAILURE;
    }

	while (std::getline(input_file, line)){
        lines.push_back(line);
    }

	std::string IP = lines[0];
	std::string username = lines[1];
	input_file.close();

	int judge = -1;
	std::string order = argv[1];


	//New User
	if(order == "new") {
		std::cout << "get user\n";
		username = get_user();
		user_changed = true;
		std::cout << "New" << std::endl;
	}

	//Manual User Modify
	else if(order == "user") {
		user_changed = true;
		if (argc == 3) {
			username = argv[2];
		}
		else if (argc == 4) {
			username = argv[2];
			judge = get_brightness(argv[3]);
		}
		else if (argc == 5) {
			username = argv[2];
			std::string order2 = argv[3];
			if (order2 == "ip") { IP = argv[4]; ip_changed = true; } 
		}
		else if (argc == 6) {
			username = argv[2];
			std::string order2 = argv[3];
			if (order2 == "ip") { IP = argv[4]; ip_changed = true; } 
			judge = get_brightness(argv[5]);
		}
		else {
			std::cerr << "No user input! Please paste the <username> after \"user\"" << std::endl;
		}	
	}

	else if(order == "ip") {
		ip_changed = true;
		if (argc == 3) {
			IP = argv[2];
		}
		else if (argc == 4) {
			IP = argv[2];
			judge = get_brightness(argv[3]);
		}
		else if (argc == 5) {
			IP = argv[2];
			std::string order2 = argv[3];
			if (order2 == "user") { username = argv[4]; user_changed = true; } 
		}
		else if (argc == 6) {
			IP = argv[2];
			std::string order2 = argv[3];
			if (order2 == "user") { username = argv[4]; user_changed = true; } 
			judge = get_brightness(argv[5]);
		}
		else {
			std::cerr << "No IP input! Please paste the bridge <IP address> after \"ip\"" << std::endl;
		}
	}
	else if(order != "new" && order != "user" && order != "ip") {
		judge = get_brightness(argv[1]);
	}

	std::string api = "http://" + IP + "/api/" + username + "/lights/1/state";
	
	if (ip_changed || user_changed) {
		if (ip_changed) {
			std::cout << "IP Modified" << std::endl;
		}
		if (user_changed) {
			std::cout << "username Modified" << std::endl;
		}
		std::ofstream output_file(filename, std::ios::trunc);
		output_file << IP << "\n" << username;
		output_file.close();
	}
	

	cpr::Url url{api};

	if (judge == 0){
		cpr::Body body1{"{\"on\": false}"};  		// JSON text string
		cpr::Response r1 = cpr::Put(url, body1);                  
		std::cout << r1.text<< std::endl;
		if (r1.text != "") {
			std::cout << "Lights off" << std::endl;
		}
		else {std::cerr << "No response from bridge!" << std::endl;}
	}
	else if (judge > 0) {
		std::string msg = "{\"on\": true, \"bri\":"+ std::to_string(judge) +"}";
		cpr::Body body2{msg};
		cpr::Response r2 = cpr::Put(url, body2);              
		std::cout << r2.text << std::endl;
		if (r2.text != "") {
			std::cout << "Brightness Changed" << std::endl;
		}
		else {std::cerr << "No response from bridge!" << std::endl;}
	}

    return 0;
}
