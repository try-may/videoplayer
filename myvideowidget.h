#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QWidget>
#include <qvideowidget.h>
namespace Ui {
class MyVideoWidget;
}

class MyVideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit MyVideoWidget(QWidget *parent = nullptr);
    ~MyVideoWidget();
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * ev);

private:
    Ui::MyVideoWidget *ui;
};

#endif // MYVIDEOWIDGET_H
