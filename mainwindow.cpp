#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "QMediaPlayer"
#include "QVideoWidget"
#include "qaudiooutput.h"
#include "QFileDialog"
#include "QTimer"
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
using namespace Qt;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<avcodec_configuration()<<endl;
    QAudioOutput *audio=new QAudioOutput(this);
    audio->setVolume(100);
    QMediaPlayer *qmp = new QMediaPlayer();
    qmp->setAudioOutput(audio);
    qmp->setVideoOutput(ui->widget);
    qmp->setLoops(-1);
    qmp->setSource(QUrl("F:/图/横屏1分钟.mp4"));
    qmp->play();
    ui->pushButton->setText("暂停");
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        if(qmp->playbackState()==QMediaPlayer::PlayingState)
        {
            ui->pushButton->setText("播放");
            qmp->pause();
        }
        else
        {
            qmp->play();
            ui->pushButton->setText("暂停");
        }
    });
    QTimer * timer= new QTimer(this);
    timer->start(500);
    connect(qmp,&QMediaPlayer::sourceChanged,[=](){
        qmp->play();
        timer->start();
    });

    connect(ui->pushButton_2,&QPushButton::clicked,[=]{

        QString path = QFileDialog::getOpenFileName(this,"选择文件","/","*.mp4 *.mp3");
        qmp->stop();
        qmp->setPlaybackRate(1.0);
        ui->horizontalSlider->setValue(0);
        timer->stop();
        qmp->setSource(QUrl(path));
    });
    connect(qmp,&QMediaPlayer::durationChanged,[=](){

        playtime = qmp->duration();
        ui->label->setText("0/"+QString::number(playtime));
//        qDebug()<<playtime;
    });
    qmp->setPlaybackRate(1.0);
    static double rate=1.0;
    connect(ui->pushButton_3,&QPushButton::clicked,[=]{
        rate=rate-0.1;
        qmp->setPlaybackRate(rate);
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=]{
        rate=rate+0.1;
        qmp->setPlaybackRate(rate);
    });

    connect(timer,&QTimer::timeout,[=]{
        ui->label->setText(timeformat(qmp->position())+'/'+timeformat(playtime));
        ui->horizontalSlider->setValue(qmp->position()*100/playtime);
//        qDebug()<<timeformat(qmp->position());
    });
    connect(ui->horizontalSlider,&QSlider::sliderPressed,[=]{
        timer->stop();
    });
    connect(ui->horizontalSlider,&QSlider::sliderReleased,[=]{
        qmp->setPosition(ui->horizontalSlider->value()*playtime/100);
        timer->start();
    });
    ui->verticalSlider->setValue(100);
    connect(ui->verticalSlider,&QSlider::valueChanged,[=](int value){
        audio->setVolume(value);
//        qDebug()<<value;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::timeformat(int time)
{
    time = time/1000;
    QString hh = QString::number(time/3600);
    QString mm = QString::number(time%3600/60);
    QString ss = QString::number(time%60);
    if(hh>="0"&&hh.length()==1)
        hh='0'+hh;
    if(mm>="0"&&mm.length()==1)
        mm='0'+mm;
    if(ss>="0"&&ss.length()==1)
        ss='0'+ss;
    return hh+':'+mm+':'+ss;
}

