#include "mywidget.h"
#include<iostream>
#include<ctime>
#include<random>
using namespace std;

void MyWidget::paintEvent(QPaintEvent *event)
{
      int pixel[32][24];
          srand(time(0));
          for(int k = 0; k < 32; k++){
               for(int l = 0;l < 24; l++){
                   pixel[k][l] = (10 + rand() % (40 - 10 + 1));
}
}



           QPainter painter(this);

//(0,0)
//    painter.drawPoint(10,10);
//(0,1)
//    painter.drawPoint(10,30);
 for(int i=0;i<3;i++) {
 	for(int j =0;j<10;j++) {
        	int  Pixel =  pixel[i][j];
		if(Pixel==30){
  		QPen mypen(QColor(Qt::blue));
	 	mypen.setWidth(20);
         	painter.setPen(mypen);
	}
        else if(Pixel==40){
 	QPen mypen(QColor(Qt::darkBlue));
         mypen.setWidth(20);
         painter.setPen(mypen);

	}
        else if(Pixel==50){
        QPen mypen(QColor(Qt::green));
         mypen.setWidth(20);
         painter.setPen(mypen);

        }
       else if(Pixel==60){
        QPen mypen(QColor(Qt::yellow));
         mypen.setWidth(20);
         painter.setPen(mypen);

        }
     else 
     {
        QPen mypen(QColor(Qt::black));
         mypen.setWidth(20);
         painter.setPen(mypen);

        }

 painter.drawPoint((2*i-1)*10,(2*j-1)*10);
 cout<<"pixel1 is "<<endl;
 cout<<Pixel<<endl;
 }

}
}

