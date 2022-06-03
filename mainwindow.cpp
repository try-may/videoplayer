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
#include <ui_dialog2.h>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
QStringList allformat = {"mp3","mp4","flac","wmv","wvx","asf","asx","wpl","wm","wmx","wmd","wmz","vob","avi","mpeg","mpg","mpe","m1v"};
QStringList audioformat = {"mp3","flac","wmv","wvx","asf","asx","wpl","wm","wmx","wmd"};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化
    init();
    connect(ui->Fullscreenbtn,&QPushButton::clicked,this,[=]{
        ui->videowidget->setFullScreen(true);
    });
    //隐藏和显示列表
    connect(ui->Playlistbtn,&QPushButton::clicked,this,[=]{
        if(ui->PlaylistWidget->isHidden())
        {
            ui->PlaylistWidget->show();

        }
        else
        {
            ui->PlaylistWidget->hide();

        }

    });
    //新建专辑
    connect(addwidget->ui->buttonBox,&QDialogButtonBox::accepted,this,[=]{
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
                if(row==-1)
                    continue;
                if(row<=nowplayrow&&now_tab==nowplaytab)
                {
                    nowplayrow--;
                }
                pltable[now_tab]->removeRow(row);
                playlist[now_tab].remove(row);

            }
        }

    });
    //增加专辑项目
    connect(ui->Addsourcebtn,&QPushButton::clicked,this,[=]{
        QStringList paths = QFileDialog::getOpenFileNames(this,"选择文件","/","*.mp4 *.mp3 *.flac *.wmv *.wvx *.asf *.wm *.wmx *.wmz *.vob *.avi *.mpeg *.mpg *.mpe *.m1v");
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
    connect(ui->ClearAllbtn,&QPushButton::clicked,this,[=]{
        playlist[now_tab].clear();
        pltable[now_tab]->clearContents();
        pltable[now_tab]->setRowCount(0);
    });

//    qDebug()<<avcodec_configuration()<<Qt::endl;
    //播放功能
    audio=new QAudioOutput(this);
    audio->setVolume(0.5);
    qmp = new QMediaPlayer();
    qmp->setAudioOutput(audio);
    qmp->setVideoOutput(ui->videowidget);
    timer= new QTimer(this);
    qmp->setLoops(1);
    ui->playmodebtn->setpic(":/pic/resource/pic/listplay.png");
    //播放与暂停
    connect(ui->Playbtn,&QPushButton::clicked,this,[=](){
        if(qmp->source()==QUrl("")&&!playlist[0].empty())
        {
            pltable[0]->selectRow(0);
            nowplaypath = playlist[0][0]->path;
            qmp->setSource(QUrl(playlist[0][0]->path));

        }
        else if(qmp->source()!=QUrl(""))
            play();
    });
    //播放状态改变
    connect(qmp,&QMediaPlayer::playbackStateChanged,this,[=](QMediaPlayer::PlaybackState newState){
//        qDebug()<<newState;
        if(newState==QMediaPlayer::PlayingState)
            ui->Playbtn->setpic(":/pic/resource/pic/pause.png");
        else
        {
            ui->Playbtn->setpic(":/pic/resource/pic/play.png");

            if(newState==QMediaPlayer::StoppedState&&qmp->position()==playtime&&qmp->loops()==1)
            {
                nowplayrow=(nowplayrow+1)%playlist[nowplaytab].size();
                nowplaypath = playlist[nowplaytab][nowplayrow]->path;
                qmp->setSource(QUrl(playlist[nowplaytab][nowplayrow]->path));
                pltable[nowplaytab]->selectRow(nowplayrow);
                qmp->play();
            }
        }

    });
    connect(qmp,&QMediaPlayer::metaDataChanged,this,[=](){
        //QMediaMetaData data=qmp->metaData();
        //        for(int i=0;i<data.keys().count();i++)
        //        {
        //            qDebug()<<data.keys()[i];
        //            qDebug()<<data.stringValue(data.keys()[i]);
        //        }
        //*******李凯捷修改
        get_zhenlv_zhenms(nowplaypath);   //更改zhenlv zhenms为当前视频对应值
//        qDebug()<<"zhenlv:"<<zhenlv;
//        qDebug()<<"zhenms:"<<zhenms;
        show_cover(nowplaypath);          //在label_2显示音频对应专辑封面
        //*******李凯捷修改

    });
    //换源信号
    connect(qmp,&QMediaPlayer::sourceChanged,this,[=](){
        this->setWindowTitle(playlist[nowplaytab][nowplayrow]->path);
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
        if(audioformat.contains(m->name.split('.').last()))
        {
            ui->videowidget->setVisible(false);
            ui->label_3->setVisible(true);
            ui->Fullscreenbtn->setEnabled(false);
        }
        else
        {
            ui->videowidget->setVisible(true);
            ui->label_3->setVisible(false);
            ui->Fullscreenbtn->setEnabled(true);
        }
        qmp->play();
        timer->start(500);

    });
    //上下曲
    connect(ui->Nextbtn,&QPushButton::clicked,this,[=](){
        pltable[nowplaytab]->clearSelection();
        nowplayrow=(nowplayrow+1)%playlist[nowplaytab].size();
        pltable[nowplaytab]->selectRow(nowplayrow);
        changesource(playlist[nowplaytab][nowplayrow]->path);
    });
    connect(ui->Prebtn,&QPushButton::clicked,this,[=](){
        pltable[nowplaytab]->clearSelection();
        nowplayrow=(nowplayrow-1+playlist[nowplaytab].size())%playlist[nowplaytab].size();
        pltable[nowplaytab]->selectRow(nowplayrow);
        changesource(playlist[nowplaytab][nowplayrow]->path);
    });
    //打开文件
    connect(ui->Openbtn,&QPushButton::clicked,this,&MainWindow::slotopenfile);
    //播放时长变化
    connect(qmp,&QMediaPlayer::durationChanged,this,[=](){
        playtime = qmp->duration();
        ui->label->setText("00:00:00/"+timeformat(playtime));
        if(nowplaytab!=1)
            pltable[nowplaytab]->setItem(nowplayrow,1,new QTableWidgetItem(timeformat(playtime)));
        if(playtime!=0)
            pltable[1]->setItem(0,1,new QTableWidgetItem(timeformat(playtime)));
    });
    //倍速
    qmp->setPlaybackRate(1.0);
    //进度条相关
    connect(timer,&QTimer::timeout,this,[=]{
        if(qmp->position()!=0)
        {
            ui->label->setText(timeformat(qmp->position())+'/'+timeformat(playtime));
            ui->horizontalSlider->setValue(qmp->position()*100/playtime);
        }
        //        qDebug()<<timeformat(qmp->position());
    });
    connect(ui->horizontalSlider,&QSlider::sliderPressed,this,[=]{
        timer->stop();
    });
    connect(ui->horizontalSlider,&QSlider::sliderReleased,this,[=]{
        if(qmp->playbackState()==QMediaPlayer::PlayingState)
        {
            qmp->setPosition(ui->horizontalSlider->value()*playtime/100);
            timer->start();
        }

    });
    connect(ui->horizontalSlider,&MySlider::MousePress,this,[=]{
        timer->stop();
    });
    connect(ui->horizontalSlider,&MySlider::MouseRelease,this,[=]{
        if(qmp->playbackState()==QMediaPlayer::PlayingState)
        {
            qmp->setPosition(ui->horizontalSlider->value()*playtime/100);
            timer->start();
        }
    });
    //音量控制
    ui->VolumeSlider->setValue(50);
    ui->VolumeSlider->setToolTip("50");
    connect(ui->VolumeSlider,&QSlider::valueChanged,this,[=](int value){
        float volume = value;
        audio->setVolume(volume/100);
        ui->VolumeSlider->setToolTip(QString::number(value));
    });
    connect(ui->volumebtn,&QPushButton::clicked,this,[=](){
        if(!audio->isMuted())
        {
            audio->setMuted(true);
            ui->volumebtn->setpic(":/pic/resource/pic/muted.png");
        }
        else
        {
            audio->setMuted(false);
            ui->volumebtn->setpic(":/pic/resource/pic/volume.png");
        }
    });
    //播放模式
    connect(ui->playmodebtn,&QPushButton::clicked,this,[=](){
        if(qmp->loops()==1)
        {
            qmp->setLoops(-1);
            ui->playmodebtn->setpic(":/pic/resource/pic/loopplay.png");
        }
        else
        {
            qmp->setLoops(1);
            ui->playmodebtn->setpic(":/pic/resource/pic/listplay.png");
        }
    });
    //视频缩略图信号  *******李凯捷修改*******
    connect(ui->horizontalSlider,SIGNAL(MySliderMouseMove(double)),this,SLOT(MySliderSlot(double)));
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
    edittabwidget = new Dialog2;
    editfilewidget = new Dialog2;
    addwidget->setWindowTitle("专辑信息");
    edittabwidget->setWindowTitle("专辑信息");
    editfilewidget->setWindowTitle("文件信息");
    //    QPixmap pm = QPixmap(":/pic/resource/pic/listplay.png");
    //    ui->label_2->setPixmap(pm);
    QAction *editfile = new QAction("编辑属性");
    QAction *deltab = new QAction("删除专辑");
    QAction *editname = new QAction("专辑重命名");
    QAction *location = new QAction("定位当前歌曲");
    listmenu.addAction(location);
    listmenu.addAction(editfile);
    listmenu.addAction(editname);
    listmenu.addAction(deltab);
    connect(editfile,&QAction::triggered,this,[=]{
        //待修改
        QList<QTableWidgetItem*> items = pltable[now_tab]->selectedItems();
        for(int i=0;i<items.size();i++)
        {
            int row = pltable[now_tab]->row(items[i]);
            qDebug()<<row;
        }
        if(items.count()>2)
        {
            ui->statusbar->showMessage("选择文件数量有误",10000);
        }
        else
        {
            QSet<int> visit;
            for(int i=0;i<items.size();i++)
            {
                int row = pltable[now_tab]->row(items[i]);

                if(row==-1||visit.contains(row))
                    items.remove(i);
                visit.insert(row);
            }
            if(items.count()!=1)
            {
                ui->statusbar->showMessage("选择文件数量有误",10000);
            }
            else
            {
                editfilewidget->ui->lineEdit->setText(playlist[now_tab][pltable[now_tab]->row(items[0])]->name);

                editfilewidget->exec();
            }
        }
    });
    connect(editfilewidget->ui->buttonBox,&QDialogButtonBox::accepted,this,[=]{
        //待修改
        if(editfilewidget->ui->lineEdit->text()=="")
            ui->statusbar->showMessage("命名为空",10000);
        else
        {
            QList<QTableWidgetItem*> items = pltable[now_tab]->selectedItems();
            for(int i=0;i<items.size();i++)
            {
                int row = pltable[now_tab]->row(items[i]);
                if(row==-1)
                    items.remove(i);
            }
            int row = pltable[now_tab]->row(items[0]);
            pltable[now_tab]->setItem(row,0,new QTableWidgetItem(editfilewidget->ui->lineEdit->text()));
            playlist[now_tab][row]->name=editfilewidget->ui->lineEdit->text();
            qDebug()<<"ok!";
        }

    });
    connect(editname,&QAction::triggered,this,[=]{
        if(now_tab==1||now_tab==0)
        {
            ui->statusbar->showMessage("无更改权限",10000);
        }
        else
        {
            edittabwidget->ui->lineEdit->setText(ui->tabWidget->tabText(now_tab));
            edittabwidget->exec();
        }

    });
    connect(edittabwidget->ui->buttonBox,&QDialogButtonBox::accepted,this,[=]{
        if(edittabwidget->ui->lineEdit->text()=="")
            ui->statusbar->showMessage("命名为空",10000);
        else
        {
            QFile f("./resource/"+tabname[now_tab]+".txt");
            f.remove();
            ui->tabWidget->setTabText(now_tab,edittabwidget->ui->lineEdit->text());
            tabname[now_tab]=edittabwidget->ui->lineEdit->text();
        }
    });
    connect(deltab,&QAction::triggered,this,[=]{
        if(now_tab==1||now_tab==0)
        {
            ui->statusbar->showMessage("无删除权限",10000);
        }
        else if(now_tab==nowplaytab)
        {
            ui->statusbar->showMessage("删除专辑为当前播放专辑！",10000);
        }
        else
        {
            if(QMessageBox::Ok==QMessageBox::warning(this,"警告","确定删除专辑？",QMessageBox::Ok,QMessageBox::Cancel))
            {
                qDebug()<<"你好";
                QFile f("./resource/"+tabname[now_tab]+".txt");

                f.remove();
                playlist.remove(now_tab);
                ui->tabWidget->removeTab(now_tab);
                tabname.remove(now_tab);
                now_tab=now_tab-1;
                ui->tabWidget->setCurrentIndex(now_tab);

            }
        }

    });
    connect(location,&QAction::triggered,this,[=]{
        ui->tabWidget->setCurrentIndex(nowplaytab);
        pltable[nowplaytab]->clearSelection();
        pltable[nowplaytab]->selectRow(nowplayrow);
    });
    ui->tabWidget->setElideMode(Qt::ElideNone);
    this->setWindowTitle("Ciallo～(∠・ω< )⌒★");
    ui->PlaylistWidget->setWindowTitle("播放列表");
    ui->videowidget->setVisible(false);
    QPixmap *qp = new QPixmap(":/pic/resource/pic/logo.png");
    ui->label_3->setPixmap(*qp);
    ui->Fullscreenbtn->setEnabled(false);
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
        connect(pltable[i],&QTableWidget::cellDoubleClicked,this,[=](int row){
            nowplaytab=now_tab;
            nowplayrow=row;
            changesource(playlist[now_tab][row]->path);
        });
        connect(table,&QTableWidget::itemChanged,this,[=](QTableWidgetItem *item){
            item->setToolTip(item->text());
        });
        table->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(table,&QWidget::customContextMenuRequested,[=](){
            listmenu.exec(QCursor::pos());
        });

        pltable[i]->setRowCount(playlist[i].size());
        for(int j = 0;j<playlist[i].size();j++)
        {
            pltable[i]->setItem(j,0,new QTableWidgetItem(playlist[i][j]->name));
        }
    }
    ui->tabWidget->setCurrentIndex(now_tab);
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,[=](int index){
        if(index==ui->tabWidget->count()-1)
        {
            addwidget->show();
        }
    });

    connect(ui->tabWidget,&QTabWidget::currentChanged,this,[=](int index){
        if(index==ui->tabWidget->count()-1)
        {
            ui->tabWidget->setCurrentIndex(now_tab);
        }
        else
            now_tab = ui->tabWidget->currentIndex();

    });


    //按钮设置
    ui->Prebtn->setpic(":/pic/resource/pic/preplay.png");
    ui->Playbtn->setpic(":/pic/resource/pic/play.png");
    ui->Nextbtn->setpic(":/pic/resource/pic/nextplay.png");
    ui->Openbtn->setpic(":/pic/resource/pic/openfile.png");
    ui->volumebtn->setpic(":/pic/resource/pic/volume.png");
    ui->Fullscreenbtn->setpic(":/pic/resource/pic/fullscreen.png");
    ui->Playlistbtn->setpic(":/pic/resource/pic/playlist.png");

    //快捷键设置  *******李凯捷修改*******
//    ui->Playbtn->setShortcut(QKeySequence("Space"));
//    ui->Fullscreenbtn->setShortcut(QKeySequence("Ctrl+F"));
//    ui->Playlistbtn->setShortcut(QKeySequence("Ctrl+I"));
//    ui->Prebtn->setShortcut(QKeySequence("Ctrl+Left"));
//    ui->Nextbtn->setShortcut(QKeySequence("Ctrl+Right"));
//    ui->volup->setShortcut(QKeySequence("Ctrl+Up"));
//    ui->voldown->setShortcut(QKeySequence("Ctrl+Down"));
    ui->minus1_frame->setShortcut(QKeySequence("Ctrl+1"));
    ui->plus1_frame->setShortcut(QKeySequence("Ctrl+2"));
    ui->minus5_frame->setShortcut(QKeySequence("Ctrl+5"));
    ui->plus5_frame->setShortcut(QKeySequence("Ctrl+6"));
}
void MainWindow::newtab()
{
    QDir dir(addwidget->path);
    QString name = addwidget->ui->nametext->text();
    if (!dir.exists()&&name!="") {
        ui->statusbar->showMessage("名字不能为空！",10000);
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
        connect(table,&QTableWidget::cellDoubleClicked,this,[=](int row){
            nowplaytab=now_tab;
            nowplayrow=row;

            changesource(playlist[now_tab][row]->path);
        });
        table->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(table,&QWidget::customContextMenuRequested,this,[=](){
            listmenu.exec(QCursor::pos());
        });

        for(int j = 0;j<playlist[playlist.count()-1].size();j++)
        {
            pltable[playlist.count()-1]->setItem(j,0,new QTableWidgetItem(playlist[playlist.count()-1][j]->name));
        }
    }
}
void MainWindow::changesource(QString path)
{
    if(!QFile::exists(path))
    {
        qDebug()<<"nofile";
        ui->statusbar->showMessage("无效的播放源。",10000);
    }
    else
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

void MainWindow::slotopenfile()
{
    QString path = QFileDialog::getOpenFileName(this,"选择文件","/","*.mp4 *.mp3 *.flv *.flac *.wmv *.wvx *.asf *.wm *.wmx *.wmz *.vob *.avi *.mpeg *.mpg *.mpe *.m1v");
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
}
void MainWindow::play()
{
    if(qmp->playbackState()==QMediaPlayer::PlayingState)
    {
        ui->Playbtn->setpic(":/pic/resource/pic/play.png");
        qmp->pause();
        timer->stop();
    }
    else
    {
        qmp->play();
        ui->Playbtn->setpic(":/pic/resource/pic/pause.png");
        timer->start();
    }
}

void MainWindow::on_openfile_triggered()
{
    slotopenfile();
}


void MainWindow::on_close_triggered()
{
    this->close();
}


void MainWindow::on_fullscreen_triggered()
{
    ui->videowidget->setFullScreen(true);

}


void MainWindow::on_playlist_triggered()
{
    if(ui->PlaylistWidget->isHidden())
        ui->PlaylistWidget->show();
}


void MainWindow::on_play_triggered()
{
    ui->Playbtn->click();
}


void MainWindow::on_preplay_triggered()
{
    ui->Prebtn->click();
}


void MainWindow::on_nextplay_triggered()
{
    ui->Nextbtn->click();
}


void MainWindow::on_normal_triggered()
{
    qmp->setPlaybackRate(1.0);
    ui->statusbar->showMessage("当前为正常倍速",5000);
}
void MainWindow::on_inf_triggered()
{
    //    const char* path = nowplaypath.toLatin1();
    //     //初始化封装库
    //     //初始化网络库（可以打开rtsp，rtmp，http协议的流媒体视频）
    //     avformat_network_init();

    //     //解封装上下文
    //     AVFormatContext* ic = nullptr;//将其地址做为输入，会申请一块空间，将这块空间的地址赋给ic
    //     //解封装上下文AVFormatContext，是存储音视频封装格式中包含信息的结构体。

    //     //对视频文件进行解封装操作
    //     int re = avformat_open_input(&ic, path, 0, nullptr);//0表示自动选择解封装器,设置一个返回值知道有无错误
    //     if (re != 0)//如果返回值不是0，说明打开出现错误
    //     {
    //         char buf[1024] = { 0 };
    //         av_strerror(re, buf, sizeof(buf) - 1);//记录错误
    // //        std::cout << "open" << path << "failed!:" << buf ;//提示错误
    //         return;
    //     }
    //     re = avformat_find_stream_info(ic, 0);
    //     //获取视频流的详细信息，包括视频流与音频流
    //     av_dump_format(ic, 1, "2", 0);
    //     if (ic) {//如果封装上下文仍存在
    //         avformat_close_input(&ic);//释放资源，指针置零
    //         ic = nullptr;
    //     }
    infmation inf(this,nowplaypath);
    setFocusPolicy(Qt::NoFocus);
    inf.exec();
}

void MainWindow::on_speedup_triggered()
{
    qmp->setPlaybackRate(std::min(8.0,qmp->playbackRate()+0.1));
    ui->statusbar->showMessage("当前倍速为:"+QString::number(qmp->playbackRate()),5000);
}


void MainWindow::on_slowdown_triggered()
{
    qmp->setPlaybackRate(std::max(qmp->playbackRate()-0.1,0.5));
    ui->statusbar->showMessage("当前倍速为:"+QString::number(qmp->playbackRate()),5000);
}
//248倍速
void MainWindow::on_speed2x_triggered(){
    qmp->setPlaybackRate(2.0);
    ui->statusbar->showMessage("当前倍速为:"+QString::number(qmp->playbackRate()),5000);
}
void MainWindow::on_speed4x_triggered(){
    qmp->setPlaybackRate(4.0);
    ui->statusbar->showMessage("当前倍速为:"+QString::number(qmp->playbackRate()),5000);
}
void MainWindow::on_speed8x_triggered(){
    qmp->setPlaybackRate(8.0);
    ui->statusbar->showMessage("当前倍速为:"+QString::number(qmp->playbackRate()),5000);
}

//逐帧操作
//上1帧
void MainWindow::on_minus1_frame_triggered(){
    if(qmp->position()-int(zhenms)<=0) return;                      //如果超出进度条则返回
    if(qmp->playbackState()==QMediaPlayer::PlayingState) play();
    qmp->setPosition(qmp->position()-int(zhenms));
    //设置进度条以及时间label
    ui->label->setText(timeformat(qmp->position())+'/'+timeformat(playtime));
    ui->horizontalSlider->setValue(qmp->position()*100/playtime);
}
//下1帧
void MainWindow::on_plus1_frame_triggered(){
    if(qmp->position()+int(zhenms)>=qmp->duration()) return;        //如果超出进度条则返回
    if(qmp->playbackState()==QMediaPlayer::PlayingState) play();
    qmp->setPosition(qmp->position()+int(zhenms));
    //设置进度条以及时间label
    ui->label->setText(timeformat(qmp->position())+'/'+timeformat(playtime));
    ui->horizontalSlider->setValue(qmp->position()*100/playtime);
}
//上5帧
void MainWindow::on_minus5_frame_triggered(){
    if(qmp->position()-int(zhenms*5.0)<=0) return;                  //如果超出进度条则返回
    if(qmp->playbackState()==QMediaPlayer::PlayingState) play();
    qmp->setPosition(qmp->position()-int(zhenms*5.0));
    //设置进度条以及时间label
    ui->label->setText(timeformat(qmp->position())+'/'+timeformat(playtime));
    ui->horizontalSlider->setValue(qmp->position()*100/playtime);
}
//下5帧
void MainWindow::on_plus5_frame_triggered(){
    if(qmp->position()+int(zhenms*5.0)>=qmp->duration()) return;    //如果超出进度条则返回
    if(qmp->playbackState()==QMediaPlayer::PlayingState) play();
    qmp->setPosition(qmp->position()+int(zhenms*5.0));
    //设置进度条以及时间label
    ui->label->setText(timeformat(qmp->position())+'/'+timeformat(playtime));
    ui->horizontalSlider->setValue(qmp->position()*100/playtime);
}

//开启或者关闭视频预览
void MainWindow::on_preview_switch_triggered(){
    if(preview_on==false) {
        preview_on=true;
        ui->statusbar->showMessage("开启视频预览",5000);
        return;
    }
    if(preview_on==true) {
        preview_on=false;
        ui->statusbar->showMessage("关闭视频预览",5000);
        return;
    }
}

void MainWindow::on_muted_triggered()
{
    if(!audio->isMuted())
        audio->setMuted(true);
    else
        audio->setMuted(false);
}


void MainWindow::on_volup_triggered()
{
    audio->setVolume(audio->volume()+0.1);
    ui->VolumeSlider->setValue(audio->volume()*100);
}


void MainWindow::on_voldown_triggered()
{
    audio->setVolume(audio->volume()-0.1);
    ui->VolumeSlider->setValue(audio->volume()*100);
}

//获得视频帧率和一帧对应毫秒数
void MainWindow::get_zhenlv_zhenms(QString path){  //获得视频帧率和一帧对应毫秒数
    int ret = 0;
    AVFormatContext *format_ctx = avformat_alloc_context();
    //path.toStdString().c_str() ,将path从QString转换为const char*
    ret = avformat_open_input(&format_ctx,path.toStdString().c_str(),NULL,NULL);
    if (ret){
        //std::cout << "open failed : " << ret << std::endl;
        return ;
    }
    //AVInputFormat *input_fmt = format_ctx->iformat;
    AVStream **stream = (format_ctx->streams);
    int den = (*stream)->avg_frame_rate.den;
    int num = (*stream)->avg_frame_rate.num;
    zhenlv = (float)num/(float)den;    //帧率，每秒播放zhenlv帧
    zhenms= float(1000)/float(zhenlv);
    //qDebug()<<zhenlv;
    //qDebug()<<zhenms;
}
//显示音乐专辑封面
void MainWindow::show_cover(QString path){
    if(path.right(4)==".mp3"||path.right(5)==".flac"){
        //读取metadata
        AVFormatContext *fmt_ctx = NULL;
        AVDictionaryEntry *tag = NULL;
        //            av_register_all();
        int ret=0;
        if (ret = avformat_open_input(&fmt_ctx, path.toStdString().c_str(), NULL, NULL)){

            printf("Fail to open file");
            return;
        }
        //读取metadata中所有的tag
        while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
//            qDebug()<<tag->key<<" "<<tag->value;
        }
        //读取专辑封面图片
        if (fmt_ctx->iformat->read_header(fmt_ctx) < 0) {
            qDebug()<<"No header format";
        }
        AVPacket pkt;
        for (int i = 0; i < fmt_ctx->nb_streams; i++){

            if (fmt_ctx->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC) {

                pkt = fmt_ctx->streams[i]->attached_pic;
//                qDebug()<<pkt.data<<pkt.size;
            }
        }
        //读取完整图片数据
        QImage img=QImage::fromData((uchar*)pkt.data,pkt.size);
        //ui->widget->setStyleSheet("border-image:pk");
        ui->label_2->setPixmap(QPixmap::fromImage(img.scaled(ui->label_2->size())));  //将图片缩放至label_2大小并在label_2显示
    }
}
//鼠标对应位置视频缩略图
void MainWindow::MySliderSlot(double value){
    if(preview_on==false) return;
    if(nowplaypath.isEmpty()) return;
    if(value-(int)value>0.2) return;
    if(nowplaypath.right(4)!=".mp4") return;
    //if(de_ctx!=NULL) return;
    qDebug()<<value;
    QString proPath=QDir::currentPath();
    //    qDebug()<<proPath;

    //lkj 解决debug与exe运行目录不一致的问题
    if(proPath.right(6)=="/debug"){
        proPath=proPath.left(proPath.length()-6);
    }
    QString srcPath=nowplaypath;
    QString dstPath=proPath+"/1.jpg";
    QString start=timeformat((int)(playtime*value/100));
    qDebug()<<"start:"<<start;
    bool getMore=0;
    int num=5;
    if(sws_ctx==NULL||de_frame==NULL||en_frame==NULL||in_fmt==NULL||ou_fmt==NULL||de_ctx==NULL||en_ctx==NULL)
        doJpgGet(srcPath,dstPath,start,getMore,num);
}
//释放视频预览用到的资源
void MainWindow::releaseSources()
{
    if (in_fmt) {
        avformat_close_input(&in_fmt);
        in_fmt = NULL;
    }
    if (ou_fmt) {
        avformat_free_context(ou_fmt);
        ou_fmt = NULL;
    }

    if (en_frame) {
        av_frame_unref(en_frame);
        en_frame = NULL;
    }

    if (de_frame) {
        av_frame_unref(de_frame);
        de_frame = NULL;
    }

    if (en_ctx) {
        avcodec_free_context(&en_ctx);
        en_ctx = NULL;
    }

    if (de_ctx) {
        avcodec_free_context(&de_ctx);
        de_ctx = NULL;
    }
    //    if(sws_ctx){
    //        avcodec_free_context(&sws_ctx);
    //        sws_ctx = NULL;
    //    }
}
//获取指定位置视频预览图并显示在label_2上
void MainWindow::doJpgGet(QString srcPath,QString dstPath,QString start,bool getMore,int num)
{
    //    QString curFile(__FILE__);
    //    unsigned long pos = curFile.find("2-video_audio_advanced");
    //    if (pos == QString::npos) {
    //        qDebug()<<("not find file");
    //        return;
    //    }
    //if(sws_ctx!=NULL||de_frame!=NULL||en_frame!=NULL||in_fmt!=NULL||ou_fmt!=NULL||de_ctx!=NULL||en_ctx!=NULL) return;
    if (!getMore) {
        num = 1;
    }
    int video_index = -1;

    // 要截取的时刻
    int64_t start_pts = stoi(start.toStdString().substr(0,2))*3600;
    start_pts += stoi(start.toStdString().substr(3,2))*60;
    start_pts += stoi(start.toStdString().substr(6,2));
    //   qDebug()<<start.substr(0,2);
    //   qDebug()<<start.substr(3,2);
    //   qDebug()<<start.substr(6,2);
    qDebug()<<"start_pts:"<<start_pts;
    if (avformat_open_input(&in_fmt,srcPath.toStdString().c_str(),NULL,NULL) < 0) {
        qDebug()<<("avformat_open_input fail");
        return;
    }
    if (avformat_find_stream_info(in_fmt, NULL) < 0) {
        qDebug()<<("avformat_find_stream_info fail");
        return;
    }

    // 遍历出视频索引
    for (int i = 0; i<in_fmt->nb_streams; i++) {
        AVStream *stream = in_fmt->streams[i];
        qDebug()<<"i:"<<i;
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {   // 说明是视频
            video_index = i;
            qDebug()<<"video_index:"<<video_index;
            // 初始化解码器用于解码
            AVCodec *codec = avcodec_find_decoder(stream->codecpar->codec_id);
            de_ctx = avcodec_alloc_context3(codec);
            if (!de_ctx) {
                qDebug()<<("video avcodec_alloc_context3 fail");
                releaseSources();
                return;
            }

            // 设置解码参数，这里直接从源视频流中拷贝
            if (avcodec_parameters_to_context(de_ctx, stream->codecpar) < 0) {
                qDebug()<<("video avcodec_parameters_to_context");
                releaseSources();
                return;
            }

            // 初始化解码器上下文
            if (avcodec_open2(de_ctx, codec, NULL) < 0) {
                qDebug()<<("video avcodec_open2() fail");
                releaseSources();
                return;
            }
            //break;
        }
    }

    // 初始化编码器;因为最终是要写入到JPEG，所以使用的编码器ID为AV_CODEC_ID_MJPEG
    AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_MJPEG);
    en_ctx = avcodec_alloc_context3(codec);
    if (!en_ctx) {
        qDebug()<<("avcodec_alloc_context3 fail");
        releaseSources();
        return;
    }
    // 设置编码参数
    AVStream *in_stream = in_fmt->streams[video_index];
    en_ctx->width = in_stream->codecpar->width;
    en_ctx->height = in_stream->codecpar->height;
    // 如果是编码后写入到图片中，那么比特率可以不用设置，不影响最终的结果(也不会影响图像清晰度)
    en_ctx->bit_rate = in_stream->codecpar->bit_rate;
    // 如果是编码后写入到图片中，那么帧率可以不用设置，不影响最终的结果
    en_ctx->framerate = in_stream->r_frame_rate;
    en_ctx->time_base = in_stream->time_base;
    // 对于MJPEG编码器来说，它支持的是YUVJ420P/YUVJ422P/YUVJ444P格式的像素
    en_ctx->pix_fmt = AV_PIX_FMT_YUVJ420P;

    // 初始化编码器上下文
    if (avcodec_open2(en_ctx, codec, NULL) < 0) {
        qDebug()<<("avcodec_open2() fail");
        releaseSources();
        return;
    }


    // 创建用于输出JPG的封装器
    if (avformat_alloc_output_context2(&ou_fmt, NULL, NULL, dstPath.toStdString().c_str()) < 0) {
        qDebug()<<("avformat_alloc_output_context2");
        releaseSources();
        return;
    }

    /** 添加流
    *  对于图片封装器来说，也可以把它想象成只有一帧视频的视频封装器。所以它实际上也需要一路视频流，而事实上图片的流是视频流类型
    */
    AVStream *stream = avformat_new_stream(ou_fmt, NULL);
    // 设置流参数；直接从编码器拷贝参数即可
    if (avcodec_parameters_from_context(stream->codecpar, en_ctx) < 0) {
        qDebug()<<("avcodec_parameters_from_context");
        releaseSources();
        return;
    }

    /** 初始化上下文
    *  对于写入JPG来说，它是不需要建立输出上下文IO缓冲区的的，所以avio_open2()没有调用到，但是最终一样可以调用av_write_frame()写入数据
    */
    if (!(ou_fmt->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open2(&ou_fmt->pb, dstPath.toStdString().c_str(), AVIO_FLAG_WRITE, NULL, NULL) < 0) {
            qDebug()<<("avio_open2 fail");
            releaseSources();
            return;
        }
    }

    /** 为输出文件写入头信息
    *  不管是封装音视频文件还是图片文件，都需要调用此方法进行相关的初始化，否则av_write_frame()函数会崩溃
    */
    if (avformat_write_header(ou_fmt, NULL) < 0) {
        qDebug()<<("avformat_write_header() fail");
        releaseSources();
        return;
    }

    /** 创建视频像素转换上下文
    *  因为源视频的像素格式是yuv420p的，而jpg编码需要的像素格式是yuvj420p的，所以需要先进行像素格式转换
    */
    sws_ctx = sws_getContext(in_stream->codecpar->width, in_stream->codecpar->height, (enum AVPixelFormat)in_stream->codecpar->format,
                             en_ctx->width, en_ctx->height, en_ctx->pix_fmt,
                             0, NULL, NULL, NULL);
    if (!sws_ctx) {
        qDebug()<<("sws_getContext fail");
        releaseSources();
        return;
    }

    // 创建编码解码用的AVFrame
    de_frame = av_frame_alloc();
    en_frame = av_frame_alloc();
    en_frame->width = en_ctx->width;
    en_frame->height = en_ctx->height;
    en_frame->format = en_ctx->pix_fmt;
    if (av_frame_get_buffer(en_frame, 0) < 0) {
        qDebug()<<("av_frame_get_buffer fail");
        releaseSources();
        return;
    }
    if (av_frame_make_writable(en_frame) < 0) {
        qDebug()<<("av_frame_make_writeable fail");
        releaseSources();
        return;
    }

    AVPacket *in_pkt = av_packet_alloc();
    AVPacket *ou_pkt = av_packet_alloc();
    AVRational time_base = in_fmt->streams[video_index]->time_base;
    AVRational frame_rate = in_fmt->streams[video_index]->r_frame_rate;

    // 一帧的时间戳
    int64_t delt = (time_base.den/time_base.num)/(frame_rate.num/frame_rate.den);
    start_pts *= time_base.den/time_base.num;

    /** 因为想要截取的时间处的AVPacket并不一定是I帧，所以想要正确的解码，得先找到离想要截取的时间处往前的最近的I帧
    *  开始解码，直到拿到了想要获取的时间处的AVFrame
    *  AVSEEK_FLAG_BACKWARD 代表如果start_pts指定的时间戳处的AVPacket非I帧，那么就往前移动指针，直到找到I帧，那么
    *  当首次调用av_frame_read()函数时返回的AVPacket将为此I帧的AVPacket
    */
    if (av_seek_frame(in_fmt, video_index, start_pts, AVSEEK_FLAG_BACKWARD) < 0) {
        qDebug()<<("av_seek_frame fail");
        releaseSources();
        return;
    }

    bool found = false;
    while (av_read_frame(in_fmt, in_pkt) == 0) {

        if (in_pkt->stream_index != video_index) {
            continue;
        }

        // 先解码
        avcodec_send_packet(de_ctx, in_pkt);
        //qDebug()<<("video pts %d(%s)",in_pkt->pts,av_ts2timestr(in_pkt->pts,&in_stream->time_base));
        while (true) {

            int ret = avcodec_receive_frame(de_ctx, de_frame);
            if (ret < 0) {
                break;
            }

            /** 解码得到的AVFrame中的pts和解码前的AVPacket中的pts是一一对应的，所以可以利用AVFrame中的pts来判断此帧是否在想要截取的时间范围内
            */
            //qDebug()<<"success pts"<<de_frame->pts;
            // 成功解码出来了
            // 取多帧视频并写入到文件
            static int i=0;
            delt = delt*num;
            // 取一帧帧视频并写入到文件
            if (abs(de_frame->pts - start_pts) < delt*5.0) {
                qDebug()<<("找到了这一帧");
                // 因为源视频帧的格式和目标视频帧的格式可能不一致，所以这里需要转码
                ret = sws_scale(sws_ctx, de_frame->data, de_frame->linesize, 0, de_frame->height, en_frame->data, en_frame->linesize);
                if (ret < 0) {
                    qDebug()<<("sws_scale fail");
                    releaseSources();
                    return;
                }


                if (getMore) {
                    // 重新编码
                    en_frame->pts = i;
                    i++;
                    avcodec_send_frame(en_ctx, en_frame);
                    // 拿到指定数目的AVPacket后再清空缓冲区
                    if (i+1 > num) {
                        avcodec_send_frame(en_ctx, NULL);
                    }
                } else {
                    // 重新编码;因为只有一帧，所以这里直接写1 即可
                    en_frame->pts = 1;
                    avcodec_send_frame(en_ctx, en_frame);
                    // 因为只编码一帧，所以发送一帧视频后立马清空缓冲区
                    avcodec_send_frame(en_ctx, NULL);
                }

                ret = avcodec_receive_packet(en_ctx, ou_pkt);
                if (ret < 0) {
                    qDebug()<<("fail ");
                    releaseSources();
                    return;
                }
                if (getMore) {
                    if (i+1>num) {
                        found = true;
                    }
                } else {
                    found = true;
                }

                break;
            }
        }

        av_packet_unref(in_pkt);
        if (found) {
            qDebug()<<("has got jpg");
            break;
        }

    }

    QImage img=QImage::fromData((uchar*)ou_pkt->data,ou_pkt->size);
    ui->label_2->setPixmap(QPixmap::fromImage(img.scaled(ui->label_2->size())));
    // 释放资源
    releaseSources();
}


