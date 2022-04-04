/*
Arthor: Jiyuan He (Hjyyjh), Xiangmin Xu (Marioforest) 04.04.2022
cURL HTTP method, wrapped for Hue APIs
Relies on curl library.
*/

#ifndef HUEFUNC_H
#define HUEFUNC_H

#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>
#include "huefunc.h"

class HUEMSG{

public:

    void curlPut();
    void curlPost();
    void curlGet();

    void setURL(std::string _URL) {URL = _URL;}
    void setMessage(std::string _MSG) {MSG = _MSG;}
    
    std::string getResponse(void);

private:
    std::string URL;
    std::string MSG;
    std::string response;
    CURL *curl;

    static size_t write_callBack(void *ptr, size_t size, size_t nmemb, void *stream);
};

#endif