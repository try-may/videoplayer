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
public:
    MySlider(QWidget *parent = nullptr);
    ~MySlider();
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MYSLIDER_H
