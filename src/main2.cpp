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
#include "ansiprint.h"

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

void getframe(float data[][24]){
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

    // std::fstream fs;

    MLX90640_SetDeviceMode(MLX_I2C_ADDR, 0);
    MLX90640_SetSubPageRepeat(MLX_I2C_ADDR, 0);
    MLX90640_SetRefreshRate(MLX_I2C_ADDR, 0b010);
    MLX90640_SetChessMode(MLX_I2C_ADDR);
    //MLX90640_SetSubPage(MLX_I2C_ADDR, 0);
    std::cout << "Configured...\n";

    
    MLX90640_DumpEE(MLX_I2C_ADDR, eeMLX90640);
    MLX90640_ExtractParameters(eeMLX90640, &mlx90640);

    int refresh = MLX90640_GetRefreshRate(MLX_I2C_ADDR);
    std::cout << "EE Dumped...\n";
	
    std::thread sensor(getframe, myWidget.pixel);
    app.exec();
    sensor.join();
	
    //int frames = 30;
    //int subpage;
    
    return 0;
}

