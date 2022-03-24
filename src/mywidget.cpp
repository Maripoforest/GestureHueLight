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

using namespace std;

extern bool read_data;
double pixel_max =0;
int Pixel =0;
float temp;
int colorR = 0;
int colorG = 0;
int colorB = 0;

MyWidget::MyWidget () {

        button = new QPushButton("Reset");
        button->move(450,470);
        button->setParent(this);
        button->resize(60, 20);
        connect(button, &QPushButton::clicked, this, &MyWidget::reset);
       
        startTimer(this->intervalTime);
        resize(750, 750);

	thermo = new QwtThermo;
	thermo->move(680,100);
	thermo->setParent(this);
	thermo->setFillBrush( QBrush(Qt::red) );
	thermo->setScale(40,300);
	thermo->show();
}

void MyWidget::paintEvent(QPaintEvent *event){
        QPainter painter(this);
                for(int i = 0;i<32;i++) {
                        for(int j = 0;j<24;j++) {
                                Pixel = this->pixel[i][j];
	                  
	                        // cout << "Pixel = " << Pixel << endl;
                                if(Pixel>=0 && Pixel <= 63) {
			         	colorR = 0;
			         	colorG = 0;
			         	temp = ((float) Pixel)/64*255;
			         	// cout << temp << endl;
		                	colorB = (int) floor(temp);	     
                                     	QPen mypen(QColor(colorR,colorG,colorB));
                                     	mypen.setWidth(20);
                                     	painter.setPen(mypen);  
                                }
                                else if(Pixel >=64 && Pixel <= 127) {
                                        colorR = 0;
                                        temp = (((float) Pixel)-64)/64*255;
                                        colorG = (int) floor(temp);  
                                        temp = (127-((float) Pixel))/64*255;
                                        colorB = (int) floor(temp);
                                        QPen mypen(QColor(colorR,colorG,colorB));
                                        mypen.setWidth(20);
                                        painter.setPen(mypen);
                                }      
                                else if(Pixel >= 128 && Pixel <= 191) {
		                 	temp = (((float) Pixel)-128)/64*255;
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
			
                        // cout<<"R:"<<colorR<<" G:"<<colorG<<" B:"<<colorB<<endl;
                        painter.drawPoint((2*i-1)*10,(2*j-1)*10);
                }
        }
}

void MyWidget::reset() {
        // set up the initial plot data
        for(int i = 0;i<32;i++) {
                for(int j = 0;j<24;j++) {
                        this->pixel[i][j] = 0;
                        cout << this->pixel[i][j] << endl;
                }
        }
        read_data = true;
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
        
        if(!read_data) {
                read_data = true;
                //cout << read_data << endl;
        }
	
        this->update();
}

