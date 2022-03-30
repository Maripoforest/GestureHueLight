#include <QtGui>
#include "mywidget.h"
#include <QApplication>
#include <ctime>
#include <random>
using namespace std;
int main(int argc, char** argv ){

  QApplication app(argc, argv);
  srand(time(0));
  MyWidget myWidget;
  myWidget.show();
  myWidget.startTimer(200);
 
  return app.exec();
}
