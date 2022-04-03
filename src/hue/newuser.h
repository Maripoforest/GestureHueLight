#ifndef NEWUSER_H
#define NEWUSER_H

#include <cpr/cpr.h>
#include <iostream>
#include <string>


class newuser
{
public:
    
    std::string userip;
    std::string username;

    //constructor with default ip and userip
    newuser();

    //modify ip
    void setip(std::string _ip);
    void setusername(std::string _username);

    //request for new user
    std::string get_ip(bool& changed);
    std::string get_user(std::string ip, bool& changed);

};

#endif