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
#include <QMenu>
#include <dialog2.h>
#include "infmation.h"

extern "C" {
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/timestamp.h>
#include <libavutil/opt.h>
#include <string.h>
}

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
    void menuinit();
    void play();

    void get_zhenlv_zhenms(QString path);
    void show_cover(QString path);
    void doJpgGet(QString srcPath,QString dstPath,double start,bool getMore,double num);

public slots:
    void MySliderSlot(double value);

private slots:
    void on_inf_triggered();//显示详细信息
    void on_preview_switch_triggered();
    void slotopenfile();
    void on_openfile_triggered();

    void on_close_triggered();

    void on_fullscreen_triggered();

    void on_playlist_triggered();

    void on_play_triggered();

    void on_preplay_triggered();

    void on_nextplay_triggered();

    void on_normal_triggered();

    void on_speedup_triggered();

    void on_slowdown_triggered();
    void on_speed2x_triggered();

    void on_speed4x_triggered();

    void on_speed8x_triggered();

    void on_minus1_frame_triggered();
    void on_minus5_frame_triggered();
    void on_plus1_frame_triggered();
    void on_plus5_frame_triggered();
    void on_muted_triggered();

    void on_volup_triggered();

    void on_voldown_triggered();

private:
    Ui::MainWindow *ui;
    Dialog * addwidget;
    Dialog2 * editfilewidget;
    Dialog2 * edittabwidget;
    QAudioOutput *audio;
    QMediaPlayer *qmp;
    QTimer * timer;
    QMenu listmenu;
    qint64 playtime;
    QVector<QVector<media*>> playlist;
    QVector<MyTable *> pltable;
    QVector<QString> tabname;
    int now_tab = 0;
    int nowplaytab = 0;
    int nowplayrow = 0;
    QString nowplaypath;
//******视频预览图
    bool preview_on=false;//是否开启视频预览，false为关闭，true为开启
    float zhenlv;   //视频帧率
    float zhenms;  //视频一帧对应的毫秒数
    //视频预览图功能需要的变量
    AVFrame *de_frame=NULL;
    AVFrame *en_frame=NULL;
    // 用于视频像素转换
    SwsContext *sws_ctx;
    // 用于读取视频
    AVFormatContext *in_fmt=NULL;
    // 用于解码
    AVCodecContext *de_ctx=NULL;
    // 用于编码
    AVCodecContext *en_ctx=NULL;
    // 用于封装jpg
    AVFormatContext *ou_fmt=NULL;
    int video_ou_index;
    //释放视频预览使用到的资源
    void releaseSources();

};
#endif // MAINWINDOW_H
