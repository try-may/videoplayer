#include "myslider.h"
#include <QMouseEvent>
MySlider::MySlider(QWidget *parent):QSlider (parent)
{
    this->setMouseTracking(true);//
}
MySlider::~MySlider()
{

}
void MySlider::mousePressEvent(QMouseEvent *ev)
{
    button_pressed=true;
    QSlider::mousePressEvent(ev);
    //获取当前点击位置,得到的这个鼠标坐标是相对于当前QSlider的坐标
    int currentX = ev->pos().x();

    //获取当前点击的位置占整个Slider的百分比
    double per = currentX *1.0 /this->width();

    //利用算得的百分比得到具体数字
    int value = per*(this->maximum() - this->minimum()) + this->minimum();

    //设定滑动条位置
    this->setValue(value);

    //滑动条移动事件等事件也用到了mousePressEvent,加这句话是为了不对其产生影响，是的Slider能正常相应其他鼠标事件

    emit MousePress();
}
void MySlider::mouseReleaseEvent(QMouseEvent *event)
{
    QSlider::mouseReleaseEvent(event);

    emit MouseRelease();
    button_pressed=false;
}
//传递信号用于视频预览
void MySlider::mouseMoveEvent(QMouseEvent *ev){
    QSlider::mouseMoveEvent(ev);
    double currentX = ev->pos().x();
    double per = currentX *1.0 /this->width();
    double value = per*(double)(this->maximum() - this->minimum()) + (double)this->minimum();
    value=(int) value;
    if(value>=0&&value<=10000&&button_pressed==false)  emit MySliderMouseMove(value);
}

