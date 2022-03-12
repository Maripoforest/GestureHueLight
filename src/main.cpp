/*
Arthor: Xiangmin XU (Maripoforest) Haiyang You (rhythm232)new version
A Hue static IP and static user on/off brightness control method.
Relies on library cpr https://github.com/libcpr/cpr.git, cpr has some C++ HTTPS method that can be used to send message to the Hue light bulb api.
*/


#include <limits>
#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "fileop.h"
#include "newuser.h"

//brightness should be 0-255, integer
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

int main(int argc, char** argv) {

    std::string filename("../log.txt");
    std::vector<std::string> lines;
    newuser user;
    
    logfile log(filename);
    
    log.readfile(lines);
    user.userip = lines[0];
    user.username = lines[1];
    //std::cout << user.userip << user.username << std::endl;

    bool ip_changed = false;
	bool user_changed = false;

    int judge = -1;
	std::string order = argv[1];

    //New User
	if(order == "new") {
		if (user.get_ip(ip_changed) != "NOBRIDGE"){
        	user.get_user(user.userip, user_changed);
		}
		else {std::cerr << "Cannot assign new user." << std::endl;}
	}

    //Manual User Modify
	else if(order == "user") {

		if (argc == 3) {
			user.username = argv[2];
            user_changed = true;
		}
		else if (argc == 4) {
			user.username = argv[2];
            user_changed = true;
			judge = get_brightness(argv[3]);
		}
		else if (argc == 5) {
			user.username = argv[2];
            user_changed = true;
			std::string order2 = argv[3];
			if (order2 == "ip") { user.userip = argv[4]; ip_changed = true; } 
		}
		else if (argc == 6) {
			user.username = argv[2];
            user_changed = true;
			std::string order2 = argv[3];
			if (order2 == "ip") { user.userip = argv[4]; ip_changed = true; } 
			judge = get_brightness(argv[5]);
		}
		else {
			std::cerr << "No user input! Please paste the <username> after \"user\"" << std::endl;
		}	
	}

    //Manual IP modify
    else if(order == "ip") {

		if (argc == 3) {
			user.userip = argv[2];
            ip_changed = true;
		}
		else if (argc == 4) {
			user.userip = argv[2];
            ip_changed = true;
			judge = get_brightness(argv[3]);
		}
		else if (argc == 5) {
			user.userip = argv[2];
            ip_changed = true;
			std::string order2 = argv[3];
			if (order2 == "user") { user.username = argv[4]; user_changed = true; } 
		}
		else if (argc == 6) {
			user.userip = argv[2];
            ip_changed = true;
			std::string order2 = argv[3];
			if (order2 == "user") { user.username = argv[4]; user_changed = true; } 
			judge = get_brightness(argv[5]);
		}
		else {
			std::cerr << "No IP input! Please paste the bridge <IP address> after \"ip\"" << std::endl;
		}
	}

    //Only brightness orders
    else if(order != "new" && order != "user" && order != "ip") {
		judge = get_brightness(argv[1]);
	}

    //hue api address
    std::string api = "http://" + user.userip + "/api/" + user.username + "/lights/1/state";

    //change log.txt if ip or username modified
    if (ip_changed || user_changed) {
		if (ip_changed) {
			std::cout << "IP Modified" << std::endl;
		}
		if (user_changed) {
			std::cout << "username Modified" << std::endl;
		}
		std::ofstream output_file(filename, std::ios::trunc);
		output_file << user.userip << "\n" << user.username;
		output_file.close();
	}

    //using cpr to send json message to hue
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
    return EXIT_SUCCESS;
}
