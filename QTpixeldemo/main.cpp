#include <QtGui>
#include "mywidget.h"
#include<QApplication>
int main( int argc, char **argv )
{
  QApplication app( argc, argv );
 
  MyWidget myWidget;
  myWidget.show();
 
  return app.exec();
}
