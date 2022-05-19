#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "QMediaPlayer"
#include "QVideoWidget"
#include "qaudiooutput.h"
#include "QFileDialog"
#include "QTimer"
#include "QTableWidget"
#include "QHeaderView"
#include "QFile"
#include "qtextstream.h"
#include "QMessageBox"
#include "QDirIterator"
#include "QDialogButtonBox"
#include <ui_dialog.h>
#include <QKeyEvent>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
QStringList allformat = {"mp3","mp4"};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化
    init();
    connect(ui->Fullscreenbtn,&QPushButton::clicked,[=]{
        ui->widget->setFullScreen(true);
    });
    //新建专辑
    connect(addwidget->ui->buttonBox,&QDialogButtonBox::accepted,[=]{
        newtab();
    });
    //删除专辑项目
    connect(ui->Delsourcebtn,&QPushButton::clicked,this,[=]{
        QList<QTableWidgetItem*> items = pltable[now_tab]->selectedItems();
        if(items.size()==0)
        {
            QMessageBox::warning(this,"警告","没有选中的项目");
        }
        else
        {
            for(int i=0;i<items.size();i++)
            {
                int row = pltable[now_tab]->row(items[i]);
                pltable[now_tab]->removeRow(row);
                playlist[now_tab].remove(row);
            }
        }

    });
    //增加专辑项目
    connect(ui->Addsourcebtn,&QPushButton::clicked,[=]{
        QStringList paths = QFileDialog::getOpenFileNames(this,"选择文件","/","*.mp4 *.mp3 *.flv");
        for(int i = 0;i<paths.size();i++)
        {
            QStringList t = paths[i].split('/');
            media *m = new media();
            m->name = t[t.count()-1];
            m->path = paths[i];
            playlist[now_tab].append(m);
            pltable[now_tab]->setRowCount(pltable[now_tab]->rowCount()+1);
            pltable[now_tab]->setItem(playlist[now_tab].count()-1,0,new QTableWidgetItem(t[t.count()-1]));
        }
    });
    //清空专辑
    connect(ui->ClearAllbtn,&QPushButton::clicked,[=]{
        playlist[now_tab].clear();
        pltable[now_tab]->clearContents();
        pltable[now_tab]->setRowCount(0);
    });

    qDebug()<<avcodec_configuration()<<Qt::endl;
    //播放功能
    audio=new QAudioOutput(this);
    audio->setVolume(0.5);
    qmp = new QMediaPlayer();
    qmp->setAudioOutput(audio);
    qmp->setVideoOutput(ui->widget);
    timer= new QTimer(this);
    qmp->setLoops(-1);
    ui->Playbtn->setText("暂停");
    //播放与暂停
    connect(ui->Playbtn,&QPushButton::clicked,[=](){
        if(qmp->playbackState()==QMediaPlayer::PlayingState)
        {
            ui->Playbtn->setText("播放");
            qmp->pause();
        }
        else
        {
            qmp->play();
            ui->Playbtn->setText("暂停");
        }
    });
    connect(qmp,&QMediaPlayer::metaDataChanged,[=](){
        QMediaMetaData data=qmp->metaData();
        for(int i=0;i<data.keys().count();i++)
        {
            qDebug()<<data.keys()[i];
            qDebug()<<data.stringValue(data.keys()[i]);
        }

    });
    //换源信号
    connect(qmp,&QMediaPlayer::sourceChanged,[=](){  


        removesource(nowplaypath,1);
        if(playlist[1].size()>=50)
        {
            playlist[1].removeLast();
            pltable[1]->removeRow(pltable[1]->rowCount()-1);
        }
        pltable[1]->insertRow(0);
        pltable[1]->setItem(0,0,new QTableWidgetItem(nowplaypath.split('/').last()));
        media *m = new media();
        m->name = nowplaypath.split('/').last();
        m->path = nowplaypath;
        playlist[1].prepend(m);
        qmp->play();
        timer->start(500);
    });
    //上下曲
    connect(ui->Nextbtn,&QPushButton::clicked,[=](){
        nowplayrow=(nowplayrow+1)%playlist[nowplaytab].size();
        pltable[nowplaytab]->selectRow(nowplayrow);
        changesource(playlist[nowplaytab][nowplayrow]->path);
    });
    connect(ui->Prebtn,&QPushButton::clicked,[=](){
        nowplayrow=(nowplayrow-1+playlist[nowplaytab].size())%playlist[nowplaytab].size();
        pltable[nowplaytab]->selectRow(nowplayrow);
        changesource(playlist[nowplaytab][nowplayrow]->path);
    });
    //打开文件
    connect(ui->Openbtn,&QPushButton::clicked,[=]{
        QString path = QFileDialog::getOpenFileName(this,"选择文件","/","*.mp4 *.mp3 *.flv");
        if(path!="")
        {
            QStringList t = path.split('/');
            media *m = new media();
            m->name = t[t.count()-1];
            m->path = path;
            playlist[0].append(m);
            nowplaytab = 0;
            nowplayrow = playlist[0].count()-1;
            pltable[0]->setRowCount(pltable[0]->rowCount()+1);
            pltable[0]->setItem(nowplayrow,0,new QTableWidgetItem(t[t.count()-1]));
            pltable[0]->selectRow(nowplayrow);
            changesource(path);
        }
    });
    //播放时长变化
    connect(qmp,&QMediaPlayer::durationChanged,[=](){
        playtime = qmp->duration();
        ui->label->setText("00:00:00/"+timeformat(playtime));
        if(nowplaytab!=1)
        pltable[nowplaytab]->setItem(nowplayrow,1,new QTableWidgetItem(timeformat(playtime)));
        if(playtime!=0)
        pltable[1]->setItem(0,1,new QTableWidgetItem(timeformat(playtime)));
    });
    //倍速
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
    //进度条相关
    connect(timer,&QTimer::timeout,[=]{
        ui->label->setText(timeformat(qmp->position())+'/'+timeformat(playtime));
        ui->horizontalSlider->setValue(qmp->position()*100/playtime);
//        qDebug()<<timeformat(qmp->position());
    });
    connect(ui->horizontalSlider,&QSlider::sliderPressed,[=]{
        timer->stop();
    });
    connect(ui->horizontalSlider,&QSlider::sliderReleased,[=]{
        if(qmp->playbackState()==QMediaPlayer::PlayingState)
        {
            qmp->setPosition(ui->horizontalSlider->value()*playtime/100);
            timer->start();
        }

    });
    connect(ui->horizontalSlider,&MySlider::MousePress,[=]{
        timer->stop();
    });
    connect(ui->horizontalSlider,&MySlider::MouseRelease,[=]{
        if(qmp->playbackState()==QMediaPlayer::PlayingState)
        {
            qmp->setPosition(ui->horizontalSlider->value()*playtime/100);
            timer->start();
        }

    });
    //音量控制
    ui->verticalSlider->setValue(50);
    connect(ui->verticalSlider,&QSlider::valueChanged,[=](int value){
        float volume = value;
        audio->setVolume(volume/100);
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
void MainWindow::removesource(QString path,int i)
{
    for(int j=0;j<playlist[i].size();j++)
    {
        if(playlist[i][j]->path==path)
        {
            playlist[i].remove(j);
            pltable[i]->removeRow(j);
            return;
        }
    }
}
void MainWindow::init()
{

    addwidget=new Dialog;
    ui->tabWidget->setElideMode(Qt::ElideNone);
    QFile fl("./resource/专辑名称.txt");
    if(fl.open(QIODevice::ReadOnly))
    {
        QTextStream t(&fl);
        QString buf;
        while(!t.atEnd())
        {
            t>>buf;
            tabname.append(buf);
        }
    }
    fl.close();

    for(int i = 0;i<tabname.size();i++)
    {
        QString path = "./resource/"+tabname[i]+".txt";
        QFile fp(path);
        if(fp.open(QIODevice::ReadOnly))
        {
            QTextStream ts(&fp);
            QString buf;
            playlist.append(QVector<media*>());
            while(!ts.atEnd())
            {
                buf=ts.readLine();
                media * m =new media();
                m->name = buf;
                buf=ts.readLine();
                m->path = buf;
                playlist[i].append(m);
            }
        }
    }
    for(int i = 0;i<playlist.size();i++)
    {
        QWidget *wid = new QWidget();
        MyTable *table = new MyTable();
//        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//        table->setColumnCount(2);
        QVBoxLayout *layout = new QVBoxLayout(wid);
        layout->addWidget(table);
        ui->tabWidget->insertTab(ui->tabWidget->count()-1,wid,tabname[i]);
        pltable.append(table);
        connect(pltable[i],&QTableWidget::cellDoubleClicked,[=](int row){
            nowplaytab=now_tab;
            nowplayrow=row;
            changesource(playlist[now_tab][row]->path);
        });
        pltable[i]->setRowCount(playlist[i].size());
        for(int j = 0;j<playlist[i].size();j++)
        {
            pltable[i]->setItem(j,0,new QTableWidgetItem(playlist[i][j]->name));
        }
    }
    ui->tabWidget->setCurrentIndex(now_tab);
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,[=](int index){
        if(index==ui->tabWidget->count()-1)
        {
            addwidget->show();
        }
    });
    connect(ui->tabWidget,&QTabWidget::currentChanged,[=](int index){
        if(index==ui->tabWidget->count()-1)
        {
            ui->tabWidget->setCurrentIndex(now_tab);
        }
        else
            now_tab = ui->tabWidget->currentIndex();

    });
}
void MainWindow::newtab()
{
    QDir dir(addwidget->path);
    QString name = addwidget->ui->nametext->text();
    if (!dir.exists()&&name!="") {
        qDebug() << "dir is null";
    }
    else
    {
        tabname.append(name);
        playlist.append(QVector<media *>());
        QWidget *wid = new QWidget();
        MyTable *table = new MyTable();
//            table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//            table->setColumnCount(2);
        QVBoxLayout *layout = new QVBoxLayout(wid);
        layout->addWidget(table);
        ui->tabWidget->insertTab(ui->tabWidget->count()-1,wid,name);
        pltable.append(table);
        dir.setFilter(QDir::Files);
        QDirIterator iterator(dir);
        while(iterator.hasNext()) {
            QFileInfo info(iterator.next());
            QString name = info.fileName(); //获取文件名
            QString fileName = info.filePath(); //文件目录+文件名
            QStringList t = name.split('.');
            if(allformat.contains(t[t.count()-1]))
            {
                media * m = new media();
                m->name=name;
                m->path=fileName;
                playlist[playlist.count()-1].append(m);
            }
        }
        pltable[playlist.count()-1]->setRowCount(playlist[playlist.count()-1].size());
        connect(table,&QTableWidget::cellDoubleClicked,[=](int row){
            nowplaytab=now_tab;
            nowplayrow=row;

            changesource(playlist[now_tab][row]->path);
        });
        for(int j = 0;j<playlist[playlist.count()-1].size();j++)
        {
            pltable[playlist.count()-1]->setItem(j,0,new QTableWidgetItem(playlist[playlist.count()-1][j]->name));
        }
    }
}
void MainWindow::changesource(QString path)
{
    if(qmp->source()!=QUrl(path))
    {
        qmp->stop();
        qmp->setPlaybackRate(1.0);
        ui->horizontalSlider->setValue(0);
        timer->stop();
        nowplaypath = path;
        qmp->setSource(QUrl(path));
    }

}
void MainWindow::closeEvent(QCloseEvent *ev)
{
    QFile f;
    QTextStream st(&f);
    f.setFileName("./resource/专辑名称.txt");
    f.open(QIODevice::WriteOnly|QIODevice::Text);
    for(int i=0;i<tabname.size();i++)
    {
        if(i==0)
        st<<tabname[i];
        else
        st<<' '<<tabname[i];
    }
    f.close();
    for(int i=0;i<playlist.size();i++)
    {
        QString path = "./resource/"+tabname[i]+".txt";
        f.setFileName(path);
        f.open(QIODevice::WriteOnly|QIODevice::Text);
        for(int j=0;j<playlist[i].size();j++)
        {
            if(j==0)
            st<<playlist[i][j]->name<<Qt::endl<<playlist[i][j]->path;
            else
            st<<Qt::endl<<playlist[i][j]->name<<Qt::endl<<playlist[i][j]->path;
        }
        f.close();
    }
    QWidget::closeEvent(ev);
}


