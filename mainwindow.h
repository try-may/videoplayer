#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qvector.h>
#include <qtablewidget.h>
#include <QLayout>
#include <dialog.h>
#include <mytable.h>
#include "qaudiooutput.h"
#include "QMediaPlayer"
#include "QMediaMetaData"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
struct media{
    QString name;
    QString path;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString timeformat(int time);
    void init();
    void newtab();
    void changesource(QString path);
    void removesource(QString path,int i);
    void closeEvent(QCloseEvent *ev);


private:
    Ui::MainWindow *ui;
    qint64 playtime;
    QVector<QVector<media*>> playlist;
    QVector<MyTable *> pltable;
    QVector<QString> tabname;
    int now_tab = 0;
    Dialog * addwidget;
    QAudioOutput *audio;
    QMediaPlayer *qmp;
    QTimer * timer;
    int nowplaytab = 0;
    int nowplayrow = 0;
    QString nowplaypath;
};
#endif // MAINWINDOW_H
