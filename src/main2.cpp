#include <cstdint>
#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <random>
#include <QtGui>
#include <QApplication>
#include "MLX90640_API.h"
#include "mywidget.h"

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

#define MLX_I2C_ADDR 0x33

bool read_data = false;
uint16_t frame[834];
paramsMLX90640 mlx90640;
static float mlx90640To[768]; /*WHY MAKING IT STATIC ?*/
int emissivity = 1;
float eTa;
int c = 1;

// void qtplot(MyWidget* mywidget) {
//     mywidget->show();
// }

void fakeframe(int data[][24]) {
    
    while(1) {
        // std::cout << read_data << std::endl;
        if (read_data) {
            for (int i=0;i<32;i++) {
                for (int j=0;j<24;j++) {
                    c = (0 + rand() % (j + i + 1));
                    data[i][j] = i + j - c;
                    // data[i][j] = mlx90640To[32 * (23-j) + i];
                    // std::cout << data[i][j] << std::endl;
                }
            }
            read_data = !read_data;
        }
    }
}

void getframe(int data[][24]){
	while (1){
        MLX90640_GetFrameData(MLX_I2C_ADDR, frame);
        // MLX90640_InterpolateOutliers(frame, eeMLX90640);
        eTa = MLX90640_GetTa(frame, &mlx90640);
        //subpage = MLX90640_GetSubPageNumber(frame);
        MLX90640_CalculateTo(frame, &mlx90640, emissivity, eTa, mlx90640To);

        MLX90640_BadPixelsCorrection((&mlx90640)->brokenPixels, mlx90640To, 1, &mlx90640);
        MLX90640_BadPixelsCorrection((&mlx90640)->outlierPixels, mlx90640To, 1, &mlx90640);
        
        if (read_data) {
            for (int i=0;i<32;i++) {
                for (int j=0;j<24;j++) {
                    data[i][j] = mlx90640To[32 * (23-j) + i];
                    // std::cout << data[i][j] << std::endl;
                }
            }
            read_data = !read_data;
        }
        //std::cout << "Subpage: " << subpage <<std::endl;
        //MLX90640_SetSubPage(MLX_I2C_ADDR,!subpage);

        // for(int x = 0; x < 32; x++){
        //     for(int y = 0; y < 24; y++){
        //         //std::cout << image[32 * y + x] << ",";
        //         float val = mlx90640To[32 * (23-y) + x];
        //         if(val > 99.99) val = 99.99;
        //         if(val > 32.0){
        //             //printf(ANSI_COLOR_MAGENTA FMT_STRING ANSI_COLOR_RESET, val);
        //             std::cout << ANSI_COLOR_MAGENTA << FMT_STRING ANSI_COLOR_RESET ;
        //         }
        //         else if(val > 29.0){
        //             //printf(ANSI_COLOR_RED FMT_STRING ANSI_COLOR_RESET, val);
        //             std::cout << ANSI_COLOR_RED << FMT_STRING ANSI_COLOR_RESET ;
        //         }
        //         else if (val > 26.0){
        //             //printf(ANSI_COLOR_YELLOW FMT_STRING ANSI_COLOR_YELLOW, val);
        //             std::cout << ANSI_COLOR_YELLOW << FMT_STRING ANSI_COLOR_RESET ;
        //         }
        //         else if ( val > 20.0 ){
        //             //printf(ANSI_COLOR_NONE FMT_STRING ANSI_COLOR_RESET, val);
        //             std::cout << ANSI_COLOR_NONE << FMT_STRING ANSI_COLOR_RESET ;
        //         }
        //         else if (val > 17.0) {
        //             //printf(ANSI_COLOR_GREEN FMT_STRING ANSI_COLOR_RESET, val);
        //             std::cout << ANSI_COLOR_GREEN << FMT_STRING ANSI_COLOR_RESET ;
        //         }
                
        //         else if (val > 10.0) {
        //             //printf(ANSI_COLOR_CYAN FMT_STRING ANSI_COLOR_RESET, val);
        //             std::cout << ANSI_COLOR_CYAN << FMT_STRING ANSI_COLOR_RESET ;
        //         }
        //         else {
        //             //printf(ANSI_COLOR_BLUE FMT_STRING ANSI_COLOR_RESET, val);
        //             std::cout << ANSI_COLOR_BLUE << FMT_STRING ANSI_COLOR_RESET ;
        //         }
                
        //     }
        //     std::cout << std::endl;
        // }
        // //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        // std::cout << "\x1b[33A";
    }
}

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    srand(time(0));
    MyWidget myWidget;
    myWidget.show();
    

    int state = 0;
    std::cout << "Starting...\n";
    static uint16_t eeMLX90640[832];
    float emissivity = 1;
    
    // static float image[768];
    float eTa;
    static uint16_t data[768*sizeof(float)];

    std::fstream fs;

    // MLX90640_SetDeviceMode(MLX_I2C_ADDR, 0);
    // MLX90640_SetSubPageRepeat(MLX_I2C_ADDR, 0);
    // MLX90640_SetRefreshRate(MLX_I2C_ADDR, 0b010);
    // MLX90640_SetChessMode(MLX_I2C_ADDR);
    // //MLX90640_SetSubPage(MLX_I2C_ADDR, 0);
    // std::cout << "Configured...\n";

    
    // MLX90640_DumpEE(MLX_I2C_ADDR, eeMLX90640);
    // MLX90640_ExtractParameters(eeMLX90640, &mlx90640);

    int refresh = MLX90640_GetRefreshRate(MLX_I2C_ADDR);
    std::cout << "EE Dumped...\n";
	
    std::thread sensor(getframe, myWidget.pixel);
    app.exec();
    sensor.join();
	
    //int frames = 30;
    //int subpage;
    
    return 0;
}

