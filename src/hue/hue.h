/*
Arthor: Xiangmin XU (Maripoforest) Haiyang You (rhythm232)
A Hue static IP and static user on/off brightness control method.
Relies on cURL lib.
*/

#ifndef HUE_H
#define HUE_H
#include <iostream>
#include <string>
#include "hue.h"

int get_brightness(std::string str);
int hue(int argc, char argv[][8]);


#endif