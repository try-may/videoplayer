#include "myvideowidget.h"
#include "qevent.h"
#include "ui_myvideowidget.h"


MyVideoWidget::MyVideoWidget(QWidget *parent) :
    QVideoWidget(parent),
    ui(new Ui::MyVideoWidget)
{
    ui->setupUi(this);
}

MyVideoWidget::~MyVideoWidget()
{
    delete ui;
}
void MyVideoWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    if(event->key()==16777216)
    this->setFullScreen(false);

}
void MyVideoWidget::mouseDoubleClickEvent(QMouseEvent * ev)
{
    if(this->isFullScreen())
    this->setFullScreen(false);
    QWidget::mouseDoubleClickEvent(ev);
}
