#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_thermo.h>
 
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget();
    int pixel[32][24] = {0};
 
protected:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent*);
   
signals:

private:
    QPushButton  *button;
    QwtThermo    *thermo;
    QVBoxLayout  *vLayout;  // vertical layout
    QHBoxLayout  *hLayout;  // horizontal layout
    QwtPlot      *plot;     /* not used in this graph, comment shall we ? */

    int intervalTime = 1000;

    void reset();

public slots:
 
};
#endif

