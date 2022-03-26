#include <iostream>
#include <stdio.h>
#include <cstdint>
#include "ansiprint.h"

void ansi_print(float* mlx90640To) {
    for(int x = 0; x < 32; x++){
            for(int y = 0; y < 24; y++){
                //std::cout << image[32 * y + x] << ",";
                float val = mlx90640To[32 * (23-y) + x];
                if(val > 99.99) val = 99.99;
                if(val > 32.0){
                    //printf(ANSI_COLOR_MAGENTA FMT_STRING ANSI_COLOR_RESET, val);
                    std::cout << ANSI_COLOR_MAGENTA << FMT_STRING ANSI_COLOR_RESET ;
                }
                else if(val > 29.0){
                    //printf(ANSI_COLOR_RED FMT_STRING ANSI_COLOR_RESET, val);
                    std::cout << ANSI_COLOR_RED << FMT_STRING ANSI_COLOR_RESET ;
                }
                else if (val > 26.0){
                    //printf(ANSI_COLOR_YELLOW FMT_STRING ANSI_COLOR_YELLOW, val);
                    std::cout << ANSI_COLOR_YELLOW << FMT_STRING ANSI_COLOR_RESET ;
                }
                else if ( val > 20.0 ){
                    //printf(ANSI_COLOR_NONE FMT_STRING ANSI_COLOR_RESET, val);
                    std::cout << ANSI_COLOR_NONE << FMT_STRING ANSI_COLOR_RESET ;
                }
                else if (val > 17.0) {
                    //printf(ANSI_COLOR_GREEN FMT_STRING ANSI_COLOR_RESET, val);
                    std::cout << ANSI_COLOR_GREEN << FMT_STRING ANSI_COLOR_RESET ;
                }
                
                else if (val > 10.0) {
                    //printf(ANSI_COLOR_CYAN FMT_STRING ANSI_COLOR_RESET, val);
                    std::cout << ANSI_COLOR_CYAN << FMT_STRING ANSI_COLOR_RESET ;
                }
                else {
                    //printf(ANSI_COLOR_BLUE FMT_STRING ANSI_COLOR_RESET, val);
                    std::cout << ANSI_COLOR_BLUE << FMT_STRING ANSI_COLOR_RESET ;
                }
                
            }
            std::cout << std::endl;
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::cout << "\x1b[33A";
}