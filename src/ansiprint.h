/*
Arthor: Xiangmin XU (Maripoforest)
MLX90640 Console print
*/

#ifndef ANSIPRINT_H
#define ANSIPRINT_H

#include <iostream>
#include <stdio.h>
#include <cstdint>
#include "ansiprint.h"


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_NONE    "\x1b[30m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//#define FMT_STRING "%+06.2f "
#define FMT_STRING "\u2588\u2588"

int ansi_print(float* mlx90640To);

#endif