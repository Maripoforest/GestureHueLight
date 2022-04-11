#include "mywidget.h"
#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <qwt/qwt_thermo.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <cmath>
#include <QLabel>
#include "hue.h"

MyWidget::MyWidget () {

        button = new QPushButton("Reset");
        button->move(650,400);
        button->setParent(this);
        button->resize(60, 20);
        connect(button, &QPushButton::clicked, this, &MyWidget::reset);
       
        // startTimer(this->intervalTime);
        resize(720, 470);

	thermo = new QwtThermo;
	thermo->move(650,20);
	thermo->setParent(this);
	thermo->setFillBrush( QBrush(Qt::blue) );
	thermo->setScale(0,40);
	thermo->setScaleMaxMajor(30);
        thermo->setAlarmEnabled(true);
        thermo->setAlarmBrush(Qt::red);
        thermo->setAlarmLevel(30);

	thermo->show();

	label = new QLabel(this);
        label->setText("max");
        label->setStyleSheet("colore:black");
        label->setGeometry(670,10,50,15);

}

void MyWidget::paintEvent(QPaintEvent *event){
        QPainter painter(this);
                for(int i = 0;i<32;i++) {
                        for(int j = 0;j<24;j++) {
                                Pixel = pixel[i][j] / 40 * 255;
                                Pixel = (Pixel >= 255) ? 254 : Pixel;
                                Pixel = (Pixel <= 0) ? 1 : Pixel;
	                        // cout << "Pixel = " << Pixel << endl;
                                if(Pixel>=0 && Pixel <= 64) {
			         	colorR = 0;
			         	colorG = 0;
			         	temp = ((float) Pixel)/64*255;
			         	// cout << temp << endl;
		                	colorB = (int) floor(temp);	     
                                     	QPen mypen(QColor(colorR,colorG,colorB));
                                     	mypen.setWidth(20);
                                     	painter.setPen(mypen);  
                                }
                                else if(Pixel >64 && Pixel <127) {
                                        colorR = 0;
                                        temp = (((float) Pixel)-64)/64*255;
                                        colorG = (int) floor(temp);  
                                        temp = (127-((float) Pixel))/64*255;
                                        colorB = (int) floor(temp);
                                        QPen mypen(QColor(colorR,colorG,colorB));
                                        mypen.setWidth(20);
                                        painter.setPen(mypen);
                                }      
                                else if(Pixel >= 127 && Pixel <= 191) {
		                 	temp = (((float) Pixel)-127)/64*255;
		                 	colorR = (int) floor(temp);
                                	colorG = 255;
                                    	colorB = 0;
                                 	QPen mypen(QColor(colorR,colorG,colorB));
                                	mypen.setWidth(20);
                                  	painter.setPen(mypen);
                                }
                                else {
		                        colorR = 255;
                                        temp = (255-((float) Pixel))/64*255;
                                        colorG = (int) floor(temp); 
                                        colorB = 0;
                                        QPen mypen(QColor(colorR,colorG,colorB));
                                        mypen.setWidth(20);
                                        painter.setPen(mypen);
                                }
			
                        // std::cout<<"P:"<<Pixel<<"R:"<<colorR<<" G:"<<colorG<<" B:"<<colorB<<std::endl;
                        painter.drawPoint((2*i-1)*10,(2*j-1)*10);
                }
        }
}

void MyWidget::reset() {
        // set up the initial plot data
        for(int i = 0;i<32;i++) {
                for(int j = 0;j<24;j++) {
                        this->pixel[i][j] = 0;
                        // cout << this->pixel[i][j] << endl;
                }
        }
        // read_data = true;
        this->update();
}

void MyWidget::timerEvent(QTimerEvent*) {
        // for(int i = 0;i<32;i++) {
        //         for(int j = 0;j<24;j++) {
        //                 this->pixel[i][j] = (10 + rand() % (200+i - 10 + 1));
        //                 if(i == 0 && j == 0) {
        //                         pixel_max = this->pixel[i][j];
        //                 }
	// 		else if(this->pixel[i][j] > pixel_max) {
	// 			pixel_max = this->pixel[i][j];
	// 		}
	// 	        // cout << this->pixel[i][j] << endl;
	// 		// cout << pixel_max << endl;
        //                 // cout<<"R:"<<colorR<<"G:"<<colorG<<"B:"<<colorB<endl;
        //         }
        // }
        // thermo->setValue(pixel_max);
   
	
        // this->update();
}

void MyWidget::hasValue(float* value) {
        int c = 0;
        
        for (int i=0;i<32;i++) {
                for (int j=0;j<24;j++) {
                    pixel[i][j] = value[32 * (23-j) + i];
                    if (pixel[i][j] > pixel_max) {
                            pixel_max = pixel[i][j];
                    }
                    if (pixel[i][j] > 30.0 && c <= 21) {
                            c++;
                    }
                    if (pixel[i][j] > 30.0 && !light_stat) {
                        char cmd1[2][8]={{"null"},{"50"}};
                        hue(2, cmd1);
                        light_stat = true;
                    }
                }
        }
        // if (c>=20 && !light_stat) {
        //         char cmd1[2][8]={{"null"},{"50"}};
        //         hue(2, cmd1);
        //         light_stat = true;
        // }
        if(c<20 && light_stat) {
                char cmd2[2][8]={{"null"},{"0"}};
                hue(2, cmd2);
                light_stat = false;
        }
        this->update();
        thermo->setValue(pixel_max);
        pixel_max = 0;
}
