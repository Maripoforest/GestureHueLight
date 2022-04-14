#include "mywidget.h"
#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <qwt/qwt_text_label.h>
#include <qwt/qwt_thermo.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <cmath>


MyWidget::MyWidget () {

        std::vector<std::string> lines;
          
        log.readfile(lines);
        user.userip = lines[0];
        user.username = lines[1];

        button1 = new QPushButton("On/Off");
        button1->move(650,370);
        button1->setToolTip(tr("Using this method will turn control off,\n please manually turn control on."));
        button1->setParent(this);
        button1->resize(80, 20);
        connect(button1, &QPushButton::clicked, this, &MyWidget::onoff);

        button2 = new QPushButton("Reset");
        button2->move(650,400);
        button2->setParent(this);
        button2->resize(60, 20);
        connect(button2, &QPushButton::clicked, this, &MyWidget::reset);
        
        button3 = new QPushButton("Ctrl On/Off");
        button3->move(650,430);
        button3->setParent(this);
        button3->resize(80, 20);
        connect(button3, &QPushButton::clicked, this, &MyWidget::ctrlonoff);

        button4 = new QPushButton("Change FR");
        button4->move(650,460);
        button4->setParent(this);
        button4->resize(80, 20);
        connect(button4, &QPushButton::clicked, this, &MyWidget::framerate);

        resize(750, 530);
        
        startTimer(this->intervalTime);
	
        thermo = new QwtThermo;
	thermo->move(650,20);
	thermo->setParent(this);
	thermo->setFillBrush( QBrush(Qt::blue) );
	thermo->setScale(0,40);
	thermo->setScaleMaxMajor(30);
        thermo->setAlarmEnabled(true);
        thermo->setAlarmBrush(Qt::red);
        thermo->setAlarmLevel(30);

	label = new QLabel(this);
        label->setText("max");
        label->setStyleSheet("colore:black");
        label->setGeometry(670,10,50,15);

	thermo->show();
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

void MyWidget::onoff() {
        controlling = false;
        if (light_stat) {
                light_stat = false;
                bri = 0;
        }
        else {
                light_stat = true; 
                bri = 50;
        }
        hueThread = new std::thread(exec, this);
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
        light_stat = false;
        bri = 0;
        hueThread = new std::thread(exec, this);
}

void MyWidget::ctrlonoff() {
        hueMsgEnd();
        if (controlling) {
                controlling = false;
        }
        else {
                controlling = true;
        }
}

void MyWidget::framerate() {
        if (!fr) {
                fr = true;
        }
        else {
                fr = false;
        }
}

void MyWidget::timerEvent(QTimerEvent*) {
        hueMsgEnd();
}

bool MyWidget::hasValue(float* value) {
        
        hotpixel = 0;
        lc = 0;
        rc = 0;
        center = false;
        upper_left = false;
        upper_right = false;

        for (int i=0;i<32;i++) {
                for (int j=0;j<24;j++) {
                        pixel[i][j] = value[32 * (23-j) + i];
                        if (pixel[i][j] > pixel_max) {
                                pixel_max = pixel[i][j];
                        }

                        if (pixel[i][j] > 30.0 && pixel[i][j] < 40.0) {
                                hotpixel++;
                        }
                        if ( i == 16 && j == 12 && pixel[i][j] > 30.0 && pixel[i][j] < 40.0) {
                                center = true;
                        }
                        if ( i > 10 && j < 12 && pixel[i][j] > 30.0 && pixel[i][j] < 40.0) {
                                rc += 1;
                        }
                        if ( i < 10 && j < 12 && pixel[i][j] > 30.0 && pixel[i][j] < 40.0) {
                                lc += 1;
                        }
                }
        }
        // std::cout << hotpixel << std::endl;

        if(controlling) {
                hueMsgEnd();
                if(rc >= 10 && rc > lc){upper_right = true; upper_left = false;}
                if(lc >= 10 && lc > rc){upper_left = true; upper_right = false;}     
                if(hotpixel>30 && hotpixel < 630) {
                        rep += 1;
                        rep %= 64500;
                        if (rep %5 == 0) {
                                if (upper_left && light_stat && !upper_right) {
                                        if (bri > 0) {
                                                bri -= 50;
                                        }
                                        else {bri = 0; light_stat = false;}
                                        std::cout << bri << "---------\n";
                                        hueThread = new std::thread(exec, this);
                                }

                                else if (upper_right && !upper_left) {
                                        if (bri < 250) {
                                                bri += 50;
                                                light_stat = true;
                                                std::cout << bri << "+++++++++\n";
                                                hueThread = new std::thread(exec, this);
                                        }
                                }
                        }
                }
                else if (hotpixel > 700) {
                        if(light_stat || bri != 0) {
                                bri = 0; 
                                light_stat = false;
                                hueThread = new std::thread(exec, this);
                        }
                        
                }
                else if(rep != 0) {
                        rep = 0;
                        std::cout  << "Reset\n";
                }
        }
        this->update();
        thermo->setValue(pixel_max);
        pixel_max = 0;
        if(fr){return true;}
        return false;
}

void MyWidget::lightCmd() {
        std::string api = "http://" + user.userip + "/api/" + user.username + "/lights/1/state";
 
        if(light_stat) {
                hm.setMessage(std::to_string(bri));
        }
        else {
                hm.setMessage("0");
        }
        hm.setURL(api);
        hm.curlPut();
        hm.getResponse();
    
}

void MyWidget::hueMsgEnd() {

        if (nullptr != hueThread) {
                hueThread->join();
                delete hueThread;
                hueThread = nullptr;
        }

}
