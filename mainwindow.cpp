#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "QMediaPlayer"
#include "QVideoWidget"
#include "qaudiooutput.h"
#include "QFileDialog"
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
    connect(qmp,&QMediaPlayer::sourceChanged,[=](){
         qmp->play();
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=]{
        QString path = QFileDialog::getOpenFileName(this,"选择文件","/","*.mp4 *.mp3");
        qmp->stop();
        qmp->setSource(QUrl(path));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

