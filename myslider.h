#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>
#include <QObject>

class MySlider : public QSlider
{
    Q_OBJECT
signals:
    void MousePress();
    void MouseRelease();
    void MySliderMouseMove(double value);  //*******李凯捷修改
public:
    bool button_pressed=false;
    MySlider(QWidget *parent = nullptr);
    ~MySlider();
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *ev);  //*******李凯捷修改
};

#endif // MYSLIDER_H
