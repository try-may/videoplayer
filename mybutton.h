#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Mybutton;
}

class Mybutton : public QPushButton
{
    Q_OBJECT

public:
    explicit Mybutton(QWidget *parent = nullptr);
    ~Mybutton();
    void setpic(QString path);

private:

};

#endif // MYBUTTON_H
