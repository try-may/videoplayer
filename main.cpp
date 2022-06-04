#include "mainwindow.h"
#include "loadfileqss.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadFileQss::setStyle(":/pic/resource/six.qss"); //加载qss 样式表，用静态方式
    MainWindow w;
    w.show();
    return a.exec();
}
