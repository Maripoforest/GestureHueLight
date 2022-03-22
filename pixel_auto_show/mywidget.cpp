#include "mywidget.h"
#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <qwt/qwt_thermo.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

using namespace std;

double pixel_max =0;
MyWidget::MyWidget () {

        // plot = new QwtPlot;
        // plot->replot();
// plot->show();

        button = new QPushButton("Reset");
        button->move(450,470);
        button->setParent(this);
        button->resize(60, 20);
        connect(button, &QPushButton::clicked, this, &MyWidget::reset);
       // vLayout = new QVBoxLayout();
       // vLayout->addWidget(button);

        // hLayout = new QHBoxLayout();
        // hLayout->addLayout(vLayout);
        // hLayout->addWidget(plot);

        // setLayout(hLayout);
        startTimer(this->intervalTime);
        resize(750, 750);

	thermo = new QwtThermo;
	thermo->move(680,100);
	thermo->setParent(this);
	thermo->setFillBrush( QBrush(Qt::red) );
	thermo->setScale(60,80);
	thermo->show();
}

void MyWidget::paintEvent(QPaintEvent *event){
        QPainter painter(this);
                for(int i = 0;i<32;i++) {
         for(int j = 0;j<24;j++) {
               int Pixel = this->pixel[i][j];
                        if(Pixel <= 15) {
                         QPen mypen(QColor(Qt::darkBlue));
                                mypen.setWidth(20);
                                painter.setPen(mypen);

               }
       else if(Pixel >=15 && Pixel <= 20) {
                 QPen mypen(QColor(Qt::blue));
               mypen.setWidth(20);
                       painter.setPen(mypen);
               }      
                       
                        else if(Pixel >= 20 && Pixel <= 25) {
                                QPen mypen(QColor(Qt::green));
                                mypen.setWidth(20);
                                painter.setPen(mypen);
                        }
                        else if(Pixel >= 25 && Pixel <= 30) {
                                QPen mypen(QColor(Qt::yellow));
                                mypen.setWidth(20);
                                painter.setPen(mypen);
                        }
                        else {
                                QPen mypen(QColor(Qt::red));
                                mypen.setWidth(20);
                                painter.setPen(mypen);
                        }
                        painter.drawPoint((2*i-1)*10,(2*j-1)*10);
                        // cout<<"pixel1 is "<<endl;
                        // cout<<Pixel<<endl;
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
        this->update();
}

void MyWidget::timerEvent(QTimerEvent*) {
        for(int i = 0;i<32;i++) {
         for(int j = 0;j<24;j++) {
                        this->pixel[i][j] = (10 + rand() % (40+i - 10 + 1));
                               pixel_max = pixel[0][0];
                        for(int i=0;i<32;i++){
				for(int j =0;j<24;j++){
				if(pixel[i][j]>pixel_max){
				
				pixel_max =pixel[i][j];
				
				}
				}
			}
		       //	cout << this->pixel[i][j] << endl;
			cout <<pixel_max<<endl;
                }
        }
	thermo->setValue(pixel_max);
        this->update();
//	thermo->setValue(pixel_max);

}
