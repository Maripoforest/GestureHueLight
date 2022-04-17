#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_thermo.h>
#include <qwt/qwt_text.h>
#include "hue/huefunc.h"
#include "hue/fileop.h"
#include "hue/newuser.h"
#include <QLabel>
 
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget();
    float pixel[32][24] = {0};
    bool hasValue(float* value);
 
protected:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent*);
   
signals:

private:
    QPushButton  *button1;
    QPushButton  *button2;
    QPushButton  *button3;
    QPushButton  *button4;

    QwtThermo    *thermo;
    QLabel *label;
    
    
    int bri = 50;
    bool fr = false;
    int intervalTime = 150;
    double pixel_max = 0;
    float Pixel =0;  
    float temp;
    int colorR = 0;
    int colorG = 0;
    int colorB = 0;
    int last_hotpixel = 0;

    bool light_stat = false;
    bool controlling = true;
    bool in_up_counting = false;
    bool in_down_counting = false;
    int hotpixel = 0;
    int lc = 0;
    int rc = 0;
    bool center = false;
    bool upper_left = false;
    bool upper_right = false;
    int rep = 0;
    
    void framerate();
    void ctrlonoff();
    void reset();
    void onoff();

    void lightCmd();
    void hueMsgEnd();
    static void exec(MyWidget* mw) {
        mw->lightCmd();
    }
    
    HUEMSG hm;
    logfile log;
    newuser user;

    std::thread* hueThread = nullptr;


public slots:
 
};
#endif
