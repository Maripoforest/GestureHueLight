#include "mywidget.h"

void MyWidget::paintEvent(QPaintEvent *event)
{
      

      QPainter painter(this);
//    QPen myPen(Qt::green,20);
//    painter.setPen(myPen);
//(0,0)
//    painter.drawPoint(10,10);
//(0,1)
//    painter.drawPoint(10,30);
 for(int i=0;i<10;i++)
{
 for(int j =0;j<10;j++)
 {
         QPen mypen(QColor(Qt::blue));
         mypen.setWidth(20);
         painter.setPen(mypen);

 painter.drawPoint((2*i-1)*10,(2*j-1)*10);
 }
}
}


