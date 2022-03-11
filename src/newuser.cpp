#include "newuser.h"
#include "fileop.h"
#include <cpr/cpr.h>
#include <iostream>
#include <string>

newuser::newuser() {
    std::vector<std::string> lines;
    logfile log("../log.txt");
    if(log.readfile(lines)) {
        this->userip = lines[0];
        this->username = lines[1];
    }
    else {
        std::cout << "Use default IP and username setting:\nIP: 192.168.0.100\nusername: S7BnUlaWvwAs6dZgYErkLO8GAWdRHTdTGi1wxwL0\n";
        this->userip = "192.168.0.100";
        this->username = "S7BnUlaWvwAs6dZgYErkLO8GAWdRHTdTGi1wxwL0";
    }
}

std::string newuser::get_ip(bool& changed) {
    std::string ip_at = "https://discovery.meethue.com";
    cpr::Url getip{ip_at};
    cpr::Response userIP = cpr::Get(getip);

    std::string info = userIP.text.substr(3, 2);
    if (info != "id") {
        std::cerr << "User request failure, using default IP address.\n" << std::endl;
    }
    else if (info == "id") {
        int qcount = 0;
        for (size_t i = 47; i < userIP.text.length(); i++) {
            if (userIP.text[i] == '\"') {
                qcount = i - 47;
                break;
            }
        }
        if(this->userip != userIP.text.substr(47, qcount)) {
            changed = true;
            this->userip = userIP.text.substr(47, qcount);
        }
        
    }   
    
    return this->userip;
}

std::string newuser::get_user(std::string ip, bool& changed) {

    std::cout << "Please press the physical hue button,\npress Enter to continue." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

	std::string yourapi = "http://" + ip + "/api";

	cpr::Url user{yourapi};
	cpr::Body user_request{"{\"devicetype\":\"Raspberrypi\"}"};

	cpr::Response userid = cpr::Post(user, user_request);
	std::cout << userid.text << std::endl;

    std::string info = userid.text.substr(3, 7);
    if (info != "success") {
        std::cerr << "User request failure, using default username.\n" << std::endl;
    }
    else if (info == "success") {
        if (this->username != userid.text.substr(25, 40)) {
            this->username = userid.text.substr(25, 40);
            changed = true;
        }
        
    }

	return this->username;
}

// void newuser::setip(std::string _ip) {
//     this->userip = _ip;
// }

// void newuser::setusername(std::string _username) {
//     this->username = _username;
// }