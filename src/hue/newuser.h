/*
Arthor: Xiangmin XU (Maripoforest) Haiyang You (rhythm232)
A Hue static IP and static user on/off brightness control method.
Relies on cURL lib.
*/

#ifndef NEWUSER_H
#define NEWUSER_H

#include <iostream>
#include <string>
#include "newuser.h"
#include "fileop.h"
#include "huefunc.h"

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

protected:
    HUEMSG hm;
};

#endif