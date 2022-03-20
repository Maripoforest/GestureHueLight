#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <qwt/qwt_plot.h>
 
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget();
    int pixel[32][24] = {0};
 
protected:
    void paintEvent(QPaintEvent *event);
    //void timerEvent(QTimerEvent *);
    int count;
   
    void timerEvent(QTimerEvent*);
   
signals:
private:
    QPushButton *button;
    QVBoxLayout  *vLayout;  // vertical layout
QHBoxLayout  *hLayout;  // horizontal layout
    QwtPlot *plot;

    int intervalTime = 200;

    void reset();

public slots:
 
};
#endif
