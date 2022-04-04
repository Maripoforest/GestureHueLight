/*
Arthor: Xiangmin XU (Maripoforest) Haiyang You (rhythm232)
A Hue static IP and static user on/off brightness control method.
Relies on cURL lib.
*/

#include <iostream>
#include <string>
#include <limits>
#include "newuser.h"

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
    hm.setURL("https://discovery.meethue.com");
    hm.curlGet();
    std::cout << "Your Hue is at:" << std::endl;
    std::string text = hm.getResponse();
    if (text == "") {
        std::cerr << "No Bridge Found.\n" << std::endl;
        return "NOBRIDGE";
    }
    std::string info = text.substr(3, 2);
    if (info != "id") {
        std::cerr << "User request failure.\n" << std::endl;
        return "NOBRIDGE";
    }
    else if (info == "id") {
        int qcount = 0;
        for (size_t i = 47; i < text.length(); i++) {
            if (text[i] == '\"') {
                qcount = i - 47;
                break;
            }
        }
        if(this->userip != text.substr(47, qcount)) {
            changed = true;
            this->userip = text.substr(47, qcount);
        }
        
    }   
    
    return this->userip;
}

std::string newuser::get_user(std::string ip, bool& changed) {
    
    std::cout << "Please press the physical hue button,\npress Enter to continue." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

	std::string yourapi = "http://" + ip + "/api";
    hm.setURL(yourapi);
    hm.setMessage("{\"devicetype\":\"Raspberrypi\"}");
    hm.curlPost();
    std::cout << "Requesting user at following IP:" << std::endl;
    std::string text = hm.getResponse();

    std::string info = text.substr(3, 7);
    if (info != "success") {
        std::cerr << "User request failure, using default username.\n" << std::endl;
    }
    else if (info == "success") {
        if (this->username != text.substr(25, 40)) {
            this->username = text.substr(25, 40);
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
