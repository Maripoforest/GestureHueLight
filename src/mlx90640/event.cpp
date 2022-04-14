#include <iostream>
#include <cstdint>
#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>
#include "mlx90640_driver.h"
#include "mywidget.h"

#include <QtGui>
#include <QApplication>


int main(int argc, char** argv){

    QApplication app( argc, argv);
    MyWidget mywidget;
    MLX90640 mlx90640;
    
    mlx90640.registerCallback(&mywidget);
    mlx90640.start();
    mywidget.show();
    app.exec();
    // getchar();
    mlx90640.stop();

    return 0;
}
