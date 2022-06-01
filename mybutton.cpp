#include "mybutton.h"


Mybutton::Mybutton(QWidget *parent) :
    QPushButton(parent)

{

}

Mybutton::~Mybutton()
{

}
void Mybutton::setpic(QString path)
{
    this->setFlat(true);
    this->setText("");
    QPixmap pix;
    pix.load(path);
    this->setFixedSize(42,42);
    this->setIcon(pix);
    this->setIconSize(QSize(20,20));
//    this->setStyleSheet("QPushButton{border-radius:20px;}");
//    this->setStyleSheet("QPushButton{border:0px;}");
}
